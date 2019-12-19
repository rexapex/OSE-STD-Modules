#pragma once
#include "../Widget.h"

namespace ose::editor
{
	class EditorDearIMGUI;

	class Launcher : public Widget
	{
	public:
		Launcher(EditorDearIMGUI & editor);
		~Launcher();

		// render the Launcher window
		void Render();

	private:
		ImTextureID games_texture_id_;
		ImTextureID profiles_texture_id_;
		ImTextureID settings_texture_id_;
	};
}

