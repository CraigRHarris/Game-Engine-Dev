#pragma once
#include "Bitmaps.h"
#include "Player.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "SDL.h"
#include "SDL_render.h"

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

enum class EntityType {
	Ground,
	Player,
	Enemy,
	Pickup
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
	Scene readscene(std::string filepath);
	void savescene(const std::string& file, const std::vector<Bitmap*>& objects);
private:
	EntityType getEntityEnumFromString(const std::string& type);
};
