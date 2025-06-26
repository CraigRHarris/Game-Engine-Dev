#pragma once
#include "nlohmann/json.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_render.h"

class Bitmap;

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

enum class EntityType {
	Ground,
	Player,
	Enemy,
	Pickup,
	Goal
};

struct SceneEntity {
	EntityType type;
	std::string filename;
	int xPos;
	int yPos;
	int direction;
	std::string ObjectName;
	bool isTransparent;
	int leftBound{ 0 };
	int rightBound{ 0 };
};

struct Scene {
	std::string name;
	std::vector<SceneEntity> entities;
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
	void savescene(const std::string& file, const std::vector<Bitmap*>& objects);
private:
	/**
	* Choosing the different items from the entities.
	* @param type
	*/
	EntityType getEntityEnumFromString(const std::string& type);
};
