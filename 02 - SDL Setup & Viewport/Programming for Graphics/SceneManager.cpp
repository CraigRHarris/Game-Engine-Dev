#include "SceneManager.h"
#include <fstream>

Scene SceneManager::readscene(std::string filepath)
{
	std::ifstream input{ filepath };

	if (!input) {
		std::cerr << "Error loading " << filepath << '\n';
		return;
	}

    json parsedData = json::parse(input);

	Scene loadedScene;

	loadedScene.name = parsedData["name"];


	for (auto& item : parsedData["entities"])
	{
		EntityType type = getEntityEnumFromString(item["type"]);

		loadedScene.entities.emplace_back(type, item["sprite"], item["xpos"], item["ypos"], item["direction"], item["transparent"]);

		if (item.contains("left"))
		{
			loadedScene.entities[loadedScene.entities.size() - 1].leftBound = item["left"];
			loadedScene.entities[loadedScene.entities.size() - 1].rightBound = item["right"];
		}
	}

	return loadedScene;
}

EntityType SceneManager::getEntityEnumFromString(const std::string& type)
{
	if (type == "enemy")
		return EntityType::Enemy;

	if (type == "player")
		return EntityType::Player;

	if (type == "pickup")
		return EntityType::Pickup;

	return EntityType::Ground;
}
