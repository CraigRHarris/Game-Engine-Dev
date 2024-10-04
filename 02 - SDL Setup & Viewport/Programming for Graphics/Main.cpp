#define GLEW_STATIC

#include <glew.h>
#include <SDL_opengl.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <SDL.h>
#include <iostream>

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std:: string &errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };                        // to help the program link for eroor messeage

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}

}



int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// making the RGBA colours for the screen 
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //32 bit inc RGBA
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //frame rate
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16); //dept is not 32 bit

	//making the window on the screen 
	SDL_Window* window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext GLContext = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if (status != GLEW_OK)
	{
		std::cout << "GLEW failed to initialize" << std::endl; // message if fail to make screen
	}

	//triangle
	float Verticies[]
	{
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5, 0.0f
	};

	//create a vertex buffer
	GLuint VertexBufferObject = 0;
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float),
		Verticies, GL_STATIC_DRAW);

	//create a vertex array object
	GLuint VertexArrayObject = 0;
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);
	glEnableVertexAttribArray(0);

	//bind vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);            
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindVertexArray(0);

	const char* VertexShaderCode =
		"#version 450\n"
		"in vec3 vp;"            
		"void main() {"
		"  gl_Position = vec4(vp, 1.0);"
		"}";

	const char* FragmentShaderCode =
		"#version 450\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 1.0, 0.5, 1.0);"// colour for the triangle
		"}";

	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);       // link and compiling the shaders
	glShaderSource(VertexShader, 1, &VertexShaderCode, NULL);
	glCompileShader(VertexShader);
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderCode, NULL);
	glCompileShader(FragmentShader);

	GLuint ShaderPrograme = glCreateProgram();        // connect the shaderss to a program
	glAttachShader(ShaderPrograme, VertexShader);
	glAttachShader(ShaderPrograme, FragmentShader);

	glLinkProgram(ShaderPrograme);
	CheckShaderError(ShaderPrograme, GL_LINK_STATUS, true,
		"Error: prgram linking failed: ");
	glValidateProgram(ShaderPrograme);
	CheckShaderError(ShaderPrograme, GL_VALIDATE_STATUS, true,
		"Error: program id invalid: ");

	glClearColor(0.0f, 0.15f, 0.3f, 1.0f); //set colours and view port
	glViewport(0, 0, 800, 600);

	while (true)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(ShaderPrograme);
		glBindVertexArray(VertexArrayObject);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SDL_Delay(16);

		SDL_GL_SwapWindow(window);


	}



	/*while (true)
	{
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //making colour and window for output
		glViewport(0, 0, 800, 600);

		SDL_GL_SwapWindow(window);
	}*/
	SDL_GL_DeleteContext(GLContext);
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit(); //cleaning the code of the data to be freash for next time
	return 0;
}