#pragma once
#include "../Widget.h"
#include "OSE-V2-STD-Modules/EngineDependencies/imgui/imgui.h"

namespace ose::editor
{
	class Launcher : public Widget
	{
	public:
		Launcher(EditorDearIMGUI & editor);
		~Launcher();

		// render the Launcher window
		void render();

	private:
		ImTextureID games_texture_id_;
		ImTextureID profiles_texture_id_;
		ImTextureID settings_texture_id_;
	};
}

