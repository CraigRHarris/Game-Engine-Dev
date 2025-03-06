#pragma once

class I_SceneNode;

class Hierarchy
{
public:

	/**
	*Added a root to the Hierarchy to help scene node.
	*@param Root
	*/
	Hierarchy(I_SceneNode* _Root);
	
	/**
	Making the hierarchy with Treenodes using the children for the hierarchy.
	*/
	void Update();

	I_SceneNode* Root;
};

