#pragma once
#include <vector>

class I_SceneNode
{
public:
	I_SceneNode* parent = nullptr;
	std::vector<I_SceneNode*> children;

	/**
	*Parent added to child then remove parent from orignal child. Then stay connected to child that is parented.
	* @param childtoAdd
	*/
	void addchild(I_SceneNode* childtoAdd);
	
	/**
	Removing child from scenenode.
	*/
	void removechild(I_SceneNode* childtoRemove);
};

