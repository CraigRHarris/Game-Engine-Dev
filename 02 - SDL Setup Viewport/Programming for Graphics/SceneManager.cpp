#include "SceneManager.h"
#include "Enemy.h"
#include "Player.h"
#include <fstream>

Scene SceneManager::readscene(std::string filepath)
{
	std::ifstream input(filepath.c_str());
	if (!input)
	{
		std::cerr << "JSON FILE: " << filepath << "Could not be opened." << std::endl;
	}

    json parsedData = json::parse(input);

	Scene loadedScene;

	loadedScene.name = parsedData["name"];


	for (auto& item : parsedData["entities"])
	{
		EntityType type = getEntityEnumFromString(item["type"]);// Looping through entities and reading their types and corresponding data

		const std::string sprite = item["sprite"];
		int  x = item["xpos"];
		int  y = item["ypos"];
		int  dir = item["direction"];
		const std::string name = item["objectname"];
		bool Transp = item["transparent"];

		loadedScene.entities.emplace_back(type, item["sprite"], item["xpos"], item["ypos"], item["direction"], item["objectname"], item["transparent"]);

		if (item.contains("left"))
		{
			loadedScene.entities[loadedScene.entities.size() - 1].leftBound = item["left"];
			loadedScene.entities[loadedScene.entities.size() - 1].rightBound = item["right"];
		}
	}

	return loadedScene;
}


void SceneManager::savescene(const std::string& file, const std::vector<Bitmap*>& objects)
{
	nlohmann::json sceneJson;
	sceneJson["name"] = "Level 1";
	sceneJson["entities"] = json::array();
	for (auto object : objects)
	{
		json entity;

		entity["type"] = object->Object;
		entity["objectname"] = object->Object;
		entity["sprite"] = object->FileName;
		SDL_Rect rect = object->GetTransformRect();
		entity["xpos"] = rect.x;
		entity["ypos"] = rect.y;
		entity["direction"] = -1;
		entity["transparent"] = true;

		/*Player* player = dynamic_cast<Player*>(object);
		if (player) {
			entity["type"] = "player";
		}

		Enemy* monster = dynamic_cast<Enemy*>(object);
		if (monster)
		{
			entity["left"] = monster->getLeftBound();
			entity["right"] = monster->getRightBound();
		}*/

		sceneJson["entities"].push_back(entity);
	}

	std::ofstream outfile{ file };

	outfile << sceneJson.dump(4);


}

EntityType SceneManager::getEntityEnumFromString(const std::string& type)
{
	if (type == "enemy")
		return EntityType::Enemy;

	if (type == "player")
		return EntityType::Player;

	if (type == "pickup")
		return EntityType::Pickup;

	if (type == "goal")
		return EntityType::Goal;

	return EntityType::Ground;
}
