#pragma once
#include "OSE-Core/Editor/Editor.h"
#include "OSE-Core/Engine/EngineTask.h"
#include "OSE-V2-STD-Modules/EngineDependencies/imgui/imgui.h"

namespace ose
{
	namespace windowing
	{
		class WindowManager;
	}
	namespace resources
	{
		class ResourceManager;
	}
	namespace editor
	{
		class Launcher;
	}
}

namespace ose::editor
{
	class EditorDearIMGUI : public Editor
	{
	public:
		EditorDearIMGUI(const windowing::WindowManager & windowManager);
		~EditorDearIMGUI();

		// called every game update for every data object in pool
		// obj is a stub object and will not be used
		///void update(EngineTask & obj) override;

		// https://github.com/ocornut/imgui/wiki/Getting-Started
		/*! /brief Initialise the ImGuiIO struct.
		*
		*   The ImGuiIO struct is the main configuration and
		*   I/O between your application and ImGui.
		*/
		void EditorDearIMGUI::Setup(const windowing::WindowManager & windowManager);

		// get a reference to the editor's resource manager
		// manages textures, etc. used only by the editor
		resources::ResourceManager & GetEditorResourceManager() const { return *editor_resource_manager_; }

	private:
		std::unique_ptr<resources::ResourceManager> editor_resource_manager_;

		// GUI used for the launcher
		std::unique_ptr<Launcher> launcher_;
	};
}
