#include "stdafx.h"
#include "Launcher.h"

namespace ose::editor
{
	Launcher::Launcher(EditorDearIMGUI & editor) : Widget(editor)
	{
		editor.GetEditorResourceManager().AddTexture("Games.png");
		editor.GetEditorResourceManager().AddTexture("Profiles.png");
		editor.GetEditorResourceManager().AddTexture("Settings.png");
		editor.GetEditorResourceManager().CreateTextures();

		// TODO - this relies on the texture being of type TextureGL, maybe this can be ported to D3D / Vulkan
//		games_texture_id_ = ImTextureID(static_cast<const TextureImpl*>(editor.GetEditorResourceManager().GetTexture("Games.png"))->GetGlTexId());
//		profiles_texture_id_ = ImTextureID(static_cast<const TextureImpl*>(editor.GetEditorResourceManager().GetTexture("Profiles.png"))->GetGlTexId());
//		settings_texture_id_ = ImTextureID(static_cast<const TextureImpl*>(editor.GetEditorResourceManager().GetTexture("Settings.png"))->GetGlTexId());
	}

	Launcher::~Launcher()
	{
		// IMPORTANT - hopefully no other GUI using these textures at the same time
		editor_.GetEditorResourceManager().RemoveTexture("Games.png");
		editor_.GetEditorResourceManager().RemoveTexture("Profiles.png");
		editor_.GetEditorResourceManager().RemoveTexture("Settings.png");
	}

	// render the Launcher window
	void Launcher::Render()
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
