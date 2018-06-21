#pragma once
#include "EditorDearIMGUI.h"

namespace ose::editor
{
	class EditorDearIMGUI;

	class Widget
	{
	public:
		Widget(EditorDearIMGUI & editor) : editor_(editor) {}
		virtual void render() = 0;

	protected:
		EditorDearIMGUI & editor_;
	};
}
