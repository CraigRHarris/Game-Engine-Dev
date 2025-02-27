#pragma once
#include <vector>

class I_SceneNode
{
public:
	I_SceneNode* parent = nullptr;
	std::vector<I_SceneNode*> children;


	void addchild(I_SceneNode* childtoAdd);
	void removechild(I_SceneNode* childtoRemove);
};

