#include <string>
#include "Bitmaps.h"
#include "TextureManager.h"
#include "SDL.h"
#include "SDL_render.h"

using namespace std;

int Bitmap::objectCount = 0;

bool Bitmap::IsColliding(Bitmap* Other)
{
	if (
		(m_x + m_w >= Other->m_x) && (m_x <= Other->m_x + Other->m_w) &&
		(m_y + m_h >= Other->m_y) && (m_y <= Other->m_y + Other->m_h)// Checks if an object's point is inside another's
		)
	{
		return true;
	}
	return false;
}



Bitmap::Bitmap(SDL_Renderer* renderer, TextureManager* texManager, std::string fileName, int xpos, int ypos, const string _ObjectName, bool useTransparency)
{
	FileName = fileName;
	Object = _ObjectName;
	if (Object == "")
	{
		Object = "Object " + std::to_string(objectCount);
		objectCount++;
	}
		//store the rander for future configuring and drawing
		_pRenderer = renderer;

		_pbitmapTexture = texManager->Load(fileName, true, renderer, m_w, m_h);

		_pbitmapSurface = texManager->_surface;

		//store the position vals
		m_x = xpos;
		m_y = ypos;
	

}



void Bitmap::SetPosition(float x, float y)
{
	m_x = x;
	m_y = y;
}
position Bitmap::GetPosition() const
{
	return { m_x, m_y };
}
Bitmap::~Bitmap()
{

}

void Bitmap::GUIDraw()
{
	ImGui::Begin("Selection");
	ImGui::Text(this->Object.c_str());

	float* TempPosAddressArry[2] = { &m_x, &m_y };
	ImGui::InputFloat2("Position:", *TempPosAddressArry);


	ImGui::End();
}

void Bitmap::GuiDrawChildGUI()
{
	ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;

	bool isNodeOpen = ImGui::TreeNodeEx(this->Object.c_str(), nodeFlags, this->Object.c_str());

	if (ImGui::IsItemClicked())
	{
		I_GuiWindow::SelectedObject = this;
		cout << "selected object is " << static_cast<Bitmap*>(I_GuiWindow::SelectedObject)->Object << endl;
	}

	if (I_GuiWindow::SelectedObject == this && ImGui::BeginDragDropSource())
	{
		ImGui::SetDragDropPayload("_TREENODE", this, sizeof(Bitmap*));
		ImGui::Text("Drag and Drop Source");
		ImGui::EndDragDropSource();
	}

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_TREENODE"))
		{
			Bitmap* PayloadAsBitmap = static_cast<Bitmap*>(I_GuiWindow::SelectedObject);
			cout << PayloadAsBitmap->Object << " on top of " << this->Object << endl;
			addchild(PayloadAsBitmap);
		}

		ImGui::EndDragDropTarget();
	}

	if (isNodeOpen)
	{
		for (int i = 0; i < children.size(); i++)
		{
			Bitmap* child = (Bitmap*)this->children[i];
			child->GuiDrawChildGUI();
		}

		if (I_GuiWindow::SelectedObject == this)
			nodeFlags |= ImGuiTreeNodeFlags_Selected;

		ImGui::TreePop();
	}

}

void Bitmap::draw()
{
	//render the bitmap at the x/y coords
	if (_pbitmapTexture)
	{
		SDL_Rect destRect = { m_x, m_y, m_w, m_h };
		SDL_RenderCopy(_pRenderer, _pbitmapTexture, NULL, &destRect);
	}
}
