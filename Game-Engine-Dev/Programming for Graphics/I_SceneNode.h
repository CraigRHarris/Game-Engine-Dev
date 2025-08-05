#pragma once
#include <vector>

class I_SceneNode
{
public:
	I_SceneNode* parent = nullptr;
	std::vector<I_SceneNode*> children;

	/**
	*Parent added to child then remove child from orignal parent. Then stay connected to child when connected to parented.
	* @param childtoAdd
	*/
	void addchild(I_SceneNode* childtoAdd);
	
	/**
	Removing child from scenenode.
	*/
	void removechild(I_SceneNode* childtoRemove);
};

