#pragma once
#include "nlohmann/json.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_render.h"
#include "Bitmaps.h"

class Goal;
class Enemy;
class Bitmap;
class Pickup;

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

struct baseObject {
	position pos;
	std::string spriteFile;
};

struct groundObject : baseObject { };

struct enemyObject : baseObject{
	position patrolData;
};

struct goalObject : baseObject {};

struct pickupObject : baseObject {};

struct Scene {
	std::string name;
	position playerPosition;
	goalObject goal;
	std::vector<enemyObject> enemies;
	std::vector<groundObject> platforms;
	std::vector<pickupObject> pickups;
};

class SceneManager
{
public:
	/**
	Reading the different json files for different scenes(levels).
	*/
	Scene readscene(std::string filepath);
	/**
	* Saving the objects in the json file for the different levels to save.
	* @param file The file of the asset.
	* @param objects The object in the scene.
	*/

	void savescene(const std::string& file, const position& playerPos, const Goal* goal, 
											const std::vector<Enemy*>& enemies, const std::vector<Bitmap*>& platforms,
											const std::vector<Pickup*>& pickups);
};
