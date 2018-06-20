#pragma once
#include "OSE-Core/Editor/Editor.h"
#include "OSE-Core/Engine/DataObject.h"
#include "OSE-V2-STD-Modules/EngineDependencies/imgui/imgui.h"
#include "OSE-Core/Windowing/WindowManager.h"

namespace ose::editor
{
	using namespace engine;
	using namespace windowing;

	class EditorDearIMGUI : public Editor
	{
	public:
		EditorDearIMGUI(const WindowManager & windowManager);
		~EditorDearIMGUI();

		// called every game update for every data object in pool
		// obj is a stub object and will not be used
		void update(DataObject & obj) override;

		// https://github.com/ocornut/imgui/wiki/Getting-Started
		/*! /brief Initialise the ImGuiIO struct.
		*
		*   The ImGuiIO struct is the main configuration and
		*   I/O between your application and ImGui.
		*/
		void EditorDearIMGUI::setup(const WindowManager & windowManager);
	};
}
