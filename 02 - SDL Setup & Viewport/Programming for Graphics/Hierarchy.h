#pragma once

class I_SceneNode;

class Hierarchy
{
public:
	Hierarchy(I_SceneNode* _Root);
	void Update();
	I_SceneNode* Root;
};

