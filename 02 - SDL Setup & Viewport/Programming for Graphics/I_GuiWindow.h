#pragma once
#include <iostream>
#include "imgui.h"

class I_GuiWindow
{
public:
	static I_GuiWindow* SelectedObject;
	static I_GuiWindow* SelectedObjectForDragging;

	virtual void GUIDraw() = 0;

};

