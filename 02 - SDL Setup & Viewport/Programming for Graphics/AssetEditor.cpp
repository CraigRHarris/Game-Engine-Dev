#include "AssetEditor.h"
#include "Game.h"
#include "Bitmaps.h"   

#include <SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"
#include "Bitmaps.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"


#include <filesystem>


AssetEditor::AssetEditor(SDL_Renderer* renderer)
{
	p_Renderer= renderer;
	std::string path = "assets";
	for (const auto& entry : std::filesystem::directory_iterator(path)) //directory_iterator(path) //recursive_
	{
		if (entry.path().extension() == ".bmp" || entry.path().extension() == ".jpg" || entry.path().extension() == ".png")
		{
			Bitmap* Asset = new Bitmap(renderer, entry.path().string(), 0, 0, true);
			content.push_back(Asset);

		}
		else if (entry.is_directory())
		{
			//std::cout << "dir " << entry << std::endl;
		}
		//debug
		//std::cout << entry.path() << std::endl;
	}







	

}

void AssetEditor::Update()
{

	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && AssetMousDrag != nullptr)
	{
		//cout << "Test" << endl;
		int x, y;
		SDL_GetMouseState(&x, &y);
		Bitmap* s = new Bitmap(p_Renderer, AssetMousDrag->FileName, x, y, true);
		//s->Transfrom.ParentSet(GameWindow::Instance().GetHirarcy());
		//sceneRoot.Children.push_back(&s->M_Transform);

		AssetMousDrag = nullptr;
	}



	ImGui::Begin("Editor");
	ImGui::BeginChild("Content Window", ImVec2(), true);
	//ImGui::BeginTable("Content browser", 3);
	;
	for (int i = 0; i < content.size(); i++)
	{
		ImGui::PushID(i);

		ImGui::ImageButton((ImTextureID)content[i]->GetTextureRef(), { 100,100 });


		//for dragging
		if (ImGui::BeginDragDropSource())
		{
			AssetMousDrag = content[i];
			ImGui::Image((ImTextureID)content[i]->GetTextureRef(), { 100,100 });
			ImGui::EndDragDropSource();
		}
		ImGui::PopID();
		ImGui::SameLine();
	}

	/////////////////////////////////For Draging

	ImGui::EndChild();
	ImGui::End();
}
