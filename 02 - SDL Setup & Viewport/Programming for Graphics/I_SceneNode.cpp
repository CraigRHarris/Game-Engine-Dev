#include "I_SceneNode.h"

void I_SceneNode::addchild(I_SceneNode* childtoAdd)
{
	if (childtoAdd->parent != nullptr)
	{
		childtoAdd->parent->removechild(childtoAdd);
	}

	childtoAdd->parent = this;
	children.push_back(childtoAdd);
}

void I_SceneNode::removechild(I_SceneNode* childtoRemove)
{
	children.erase(std::remove(children.begin(), children.end(), childtoRemove), children.end());
}
