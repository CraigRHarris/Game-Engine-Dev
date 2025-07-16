#include "SceneManager.h"
#include "Enemy.h"
#include "Goal.h"
#include "Bitmaps.h"
#include "Pickup.h"

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

	auto& playerItem = parsedData["player"];
	loadedScene.playerPosition.x = playerItem["x"];
	loadedScene.playerPosition.y = playerItem["y"];

	auto& goalItem = parsedData["goal"];
	loadedScene.goal.pos.x = goalItem["x"];
	loadedScene.goal.pos.y = goalItem["y"];
	loadedScene.goal.spriteFile = goalItem["sprite"];

	for (auto& platform : parsedData["platforms"]) {
		position pos{ platform["x"], platform["y"] };

		groundObject ground;
		ground.pos = pos;
		ground.spriteFile = platform["sprite"];

		loadedScene.platforms.push_back(ground);
	}

	for (auto& enemy : parsedData["enemies"]) {
		position pos{ enemy["x"], enemy["y"] };
		position patrol{ enemy["leftPatrol"], enemy["rightPatrol"] };

		enemyObject newEnemy;
		newEnemy.pos = pos;
		newEnemy.patrolData = patrol;
		newEnemy.spriteFile = enemy["sprite"];

		loadedScene.enemies.push_back(newEnemy);
	}

	// add pickups
	for (auto& pickup : parsedData["pickups"]) {
		position pos{ pickup["x"], pickup["y"] };

		pickupObject key;
		key.pos = pos;
		key.spriteFile = pickup["sprite"];

		loadedScene.pickups.push_back(key);
	}
	return loadedScene;
}


void SceneManager::savescene(const std::string& file, const position& playerPos, const Goal* goal,
	const std::vector<Enemy*>& enemies, const std::vector<Bitmap*>& platforms,
	const std::vector<Pickup*>& pickups)
{
	nlohmann::json sceneJson;
	sceneJson["name"] = "Level 1";
	sceneJson["enemies"] = json::array();
	sceneJson["platforms"] = json::array();
	sceneJson["pickups"] = json::array();

	json player;
	player["x"] = playerPos.x;
	player["y"] = playerPos.y;

	sceneJson["player"] = player;
	
	json _goal;
	_goal["x"] = goal->GetPosition().x;
	_goal["y"] = goal->GetPosition().y;
	_goal["sprite"] = goal->FileName;
	sceneJson["goal"] = _goal;

	for (const auto platform : platforms) {
		json plat;
		plat["x"] = goal->GetPosition().x;
		plat["y"] = goal->GetPosition().y;
		plat["sprite"] = goal->FileName;

		sceneJson["platforms"].push_back(plat);
	}

	for (const auto enemy : enemies) {
		json en;
		en["x"] = enemy->GetPosition().x;
		en["y"] = enemy->GetPosition().y;
		en["leftPatrol"] = enemy->GetPosition().x;
		en["RightPatrol"] = enemy->GetPosition().y;
		en["sprite"] = enemy->FileName;

		sceneJson["enemies"].push_back(en);
	}
	//pickups
	for (const auto pickup : pickups) {
		json pu;
		pu["x"] = pickup->GetPosition().x;
		pu["y"] = pickup->GetPosition().y;
		pu["sprite"] = pickup->FileName;

		sceneJson["pickups"].push_back(pu);
	}

	//for (auto object : objects)
	//{
	//	json entity;

	//	entity["type"] = object->Object;
	//	entity["objectname"] = object->Object;
	//	entity["sprite"] = object->FileName;
	//	SDL_Rect rect = object->GetTransformRect();
	//	entity["xpos"] = rect.x;
	//	entity["ypos"] = rect.y;
	//	entity["direction"] = -1;
	//	entity["transparent"] = true;

	//	/*Player* player = dynamic_cast<Player*>(object);
	//	if (player) {
	//		entity["type"] = "player";
	//	}

	//	Enemy* monster = dynamic_cast<Enemy*>(object);
	//	if (monster)
	//	{
	//		entity["left"] = monster->getLeftBound();
	//		entity["right"] = monster->getRightBound();
	//	}*/

	//	sceneJson["entities"].push_back(entity);
	//}

	std::ofstream outfile{ file };

	outfile << sceneJson.dump(4);
}
