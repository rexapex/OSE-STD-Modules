#pragma once

namespace ose::editor
{
	class EditorDearIMGUI;

	class Widget
	{
	public:
		Widget(EditorDearIMGUI & editor) : editor_(editor) {}
		virtual void Render() = 0;

	protected:
		EditorDearIMGUI & editor_;
	};
}
