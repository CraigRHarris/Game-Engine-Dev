  
#include "SDL.h"
#include <SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_internal.h"
#include "imgui_sdl.h"

#include <iostream>
#include <filesystem>
#include <vector>

#include "Bitmaps.h"
#include "AssetEditor.h"
#include "Game.h"
#include "Pickup.h"
#include "Enemy.h"

using namespace std;

AssetEditor::AssetEditor(SDL_Renderer* renderer, SDL_Window* window, TextureManager* texManager, Game* game) : _tManager{ texManager }
{
	_game = game;
	_Renderer= renderer;
	_Window = window;

	std::string path = "assets";
	for (const auto& entry : std::filesystem::directory_iterator(path)) 
	{
		if (entry.path().extension() == ".bmp")
		{
			Bitmap* Asset = new Bitmap(renderer, texManager, entry.path().string(), 0, 0,"", true);
			content.push_back(Asset);

		}
		else if (entry.is_directory())
		{
			cout << "dir " << entry << std::endl;
		}
		//debug
		cout << entry.path() << std::endl;
	}

	//debug
	//std::cout << entry.path() << std::endl;

}

void AssetEditor::Update()
{

	if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && AssetMouseDrag != nullptr)
	{
		cout << "Added Pickup" << endl;
		_selected = false;
		int x, y;
		SDL_GetMouseState(&x, &y);
		
		/*if (AssetMouseDrag->FileName == "assets\\monstertrans.bmp")
		{
			_game->addEntity(EntityType::Player, AssetMouseDrag->FileName, x, y, "monster", true, true);
		}
		else if (AssetMouseDrag->FileName == "assets\\Alian.bmp")
		{
			_game->addEntity(EntityType::Enemy, AssetMouseDrag->FileName, x, y, "enemy", true, true, x, y + 100);
		}
		else if (AssetMouseDrag->FileName == "assets\\Key.bmp")
		{
			_game->addEntity(EntityType::Pickup, AssetMouseDrag->FileName, x, y, "key", true, true);
		}
		else if (AssetMouseDrag->FileName == "assets\\door.bmp")
		{
			_game->addEntity(EntityType::Goal, AssetMouseDrag->FileName, x, y, "goal", true, true);
		}
		else {
			_game->addEntity(EntityType::Ground, AssetMouseDrag->FileName, x, y, "ground", true, true);
		}*/
		AssetMouseDrag = nullptr;
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
			_selected = true;
			std::cout << "BeginDragDropSource\n";
			AssetMouseDrag = content[i];
			ImGui::Image((ImTextureID)content[i]->GetTextureRef(), { 100,100 });
			ImGui::EndDragDropSource();
		}
		ImGui::PopID();
		ImGui::SameLine();
	}


	ImGui::EndChild();
	ImGui::End();
}
