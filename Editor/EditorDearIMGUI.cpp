#include "stdafx.h"
#include "EditorDearIMGUI.h"
#include "OSE-Core/Windowing/WindowManager.h"

using namespace ose::windowing;
using namespace ose::resources;

namespace ose::editor
{
	EditorDearIMGUI::EditorDearIMGUI(const WindowManager & windowManager)
	{
		Setup(windowManager);
		editor_resource_manager_ = std::make_unique<ResourceManager>("D:\\James\\Documents\\Visual Studio 2017\\Projects\\OSE V2\\OSE V2\\OSE-V2-STD-Modules\\Editor");
		launcher_ = std::make_unique<Launcher>(*this);
	}

	EditorDearIMGUI::~EditorDearIMGUI()
	{
		ImGui::DestroyContext();
	}

	// called every game update for every data object in pool
	// obj is a stub object and will not be used
	/*void EditorDearIMGUI::update(DataObject & obj)
	{
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::NewFrame();

		launcher_->render();

		ImGui::Render();
	}*/

	// https://github.com/ocornut/imgui/wiki/Getting-Started
	/*! /brief Boilerplate function for OpenGL 2.0 rendering.
	*
	*  This function isn't written by us, but is mandatory
	*  boilerplate from the library. It can be copy/pasted
	*  into your projects, but should really be part of the
	*  library itself?
	*/
	void Renderer(ImDrawData* draw_data)
	{
		ImGuiIO& io { ImGui::GetIO() };
		int fb_width { (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x) };
		int fb_height { (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y) };

		draw_data->ScaleClipRects(io.DisplayFramebufferScale);

		GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
		GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
		glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_SCISSOR_TEST);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnable(GL_TEXTURE_2D);

		// Setup viewport, orthographic projection matrix
		glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// Render command lists
#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = draw_data->CmdLists[n];
			const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
			const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();
			glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, pos)));
			glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, uv)));
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + OFFSETOF(ImDrawVert, col)));

			for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
			{
				const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
				if (pcmd->UserCallback)
				{
					pcmd->UserCallback(cmd_list, pcmd);
				}
				else
				{
					glBindTexture(GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId);
					glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
					glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof(ImDrawIdx) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer);
				}
				idx_buffer += pcmd->ElemCount;
			}
		}
#undef OFFSETOF

		// Restore modified state
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glBindTexture(GL_TEXTURE_2D, last_texture);
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glPopAttrib();
		glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
	}

	// https://github.com/ocornut/imgui/wiki/Getting-Started
	/*! /brief Initialise the ImGuiIO struct.
	*
	*   The ImGuiIO struct is the main configuration and
	*   I/O between your application and ImGui.
	*/
	void EditorDearIMGUI::Setup(const WindowManager & windowManager)
	{
		unsigned char* pixels;
		int width,
			height,
			display_width,
			display_height;
		GLuint g_FontTexture;
		ImGui::CreateContext();
		ImGuiIO& io { ImGui::GetIO() };

		io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height);

		// Upload texture to graphics system
		GLint last_texture;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
		glGenTextures(1, &g_FontTexture);
		glBindTexture(GL_TEXTURE_2D, g_FontTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);

		// Get display size
		// TODO - update window width & height on window resize callback
		// TODO - refresh IMGUI width & height on fb resize & window resize
		width = windowManager.GetWindowWidth();
		height = windowManager.GetWindowHeight();
		display_width = windowManager.GetFramebufferWidth();
		display_height = windowManager.GetFramebufferHeight();

		io.DisplaySize = ImVec2((float)width, (float)height);
		io.RenderDrawListsFn = Renderer;
		io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

		// Restore state
		glBindTexture(GL_TEXTURE_2D, last_texture);
	}
}
