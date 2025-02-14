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
	bool isTransparent;
	int leftBound;
	int rightBound;
};

struct Scene {
	std::string name;
	std::vector<SceneEntity> entities;
};

class SceneManager
{
public:
	Scene readscene(std::string filepath);

private:
	EntityType getEntityEnumFromString(const std::string& type);
};
