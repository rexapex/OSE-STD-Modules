#include "stdafx.h"
#include "Launcher.h"

namespace ose::editor
{
	Launcher::Launcher(EditorDearIMGUI & editor) : Widget(editor)
	{
		editor.get_editor_resource_manager().addTexture("Games.png");
		editor.get_editor_resource_manager().addTexture("Profiles.png");
		editor.get_editor_resource_manager().addTexture("Settings.png");
		editor.get_editor_resource_manager().createTextures();

		// TODO - this relies on the texture being of type TextureGL, maybe this can be ported to D3D / Vulkan
		games_texture_id_ = ImTextureID(static_cast<const TextureImpl*>(editor.get_editor_resource_manager().getTexture("Games.png"))->get_gl_tex_id());
		profiles_texture_id_ = ImTextureID(static_cast<const TextureImpl*>(editor.get_editor_resource_manager().getTexture("Profiles.png"))->get_gl_tex_id());
		settings_texture_id_ = ImTextureID(static_cast<const TextureImpl*>(editor.get_editor_resource_manager().getTexture("Settings.png"))->get_gl_tex_id());
	}

	Launcher::~Launcher()
	{
		// IMPORTANT - hopefully no other GUI using these textures at the same time
		editor_.get_editor_resource_manager().removeTexture("Games.png");
		editor_.get_editor_resource_manager().removeTexture("Profiles.png");
		editor_.get_editor_resource_manager().removeTexture("Settings.png");
	}

	// render the Launcher window
	void Launcher::render()
	{
		bool my_tool_active = true;

		// Create a window called "My First Tool", with a menu bar.
		ImGui::SetNextWindowSize(ImVec2(600, 400));
		ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
		
		ImGui::Columns(3);
		ImGui::ImageButton(games_texture_id_, ImVec2(128, 128));
		ImGui::NextColumn();
		ImGui::ImageButton(profiles_texture_id_, ImVec2(128, 128));
		ImGui::NextColumn();
		ImGui::ImageButton(settings_texture_id_, ImVec2(128, 128));

		ImGui::End();
	}
}
