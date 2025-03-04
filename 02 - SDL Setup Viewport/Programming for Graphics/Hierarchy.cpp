#include "Hierarchy.h"
#include "Bitmaps.h"
#include "I_SceneNode.h"
#include "I_GuiWindow.h"

Hierarchy::Hierarchy(I_SceneNode* _Root)
{
	Root = _Root;
}

void Hierarchy::Update()
{
	ImGui::Begin("Scene Hierarchy", 0);

	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;
	bool isNodeOpen = ImGui::TreeNodeEx("Scene", nodeFlags, "Scene");
	if (isNodeOpen)
	{

		for (int i = 0; i < Root->children.size(); i++)
		{
			Bitmap* Child = static_cast<Bitmap*>(Root->children[i]);
			Child->GuiDrawChildGUI();
		}
		ImGui::TreePop();
	}

	ImGui::End();
}

