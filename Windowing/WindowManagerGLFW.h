#pragma once

#define GLEW_STATIC

#include "OSE-Core/Windowing/WindowManager.h"
#include "OSE-Core/Rendering/VideoMode.h"
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>


namespace ose::windowing
{
	class WindowManagerGLFW : public WindowManager
	{
	public:
		WindowManagerGLFW();
		virtual ~WindowManagerGLFW() noexcept;
		WindowManagerGLFW(WindowManagerGLFW &) = delete;
		WindowManagerGLFW(WindowManagerGLFW &&) = delete;
		WindowManagerGLFW & operator=(WindowManagerGLFW &) = delete;
		WindowManagerGLFW & operator=(WindowManagerGLFW &&) = delete;

		const int GetFramebufferWidth() const { return fbwidth_; }
		const int GetFramebufferHeight() const { return fbheight_; }
		const int GetWindowWidth() const { return wwidth_; }
		const int GetWindowHeight() const { return wheight_; }

		std::vector<VideoMode> GetAvailableVideoModes();

		int	SetMouseVisibility(int value);

		void SetWindowSize(int width, int height);
		void SetWindowPos(int x, int y);

		void SetTitle(const std::string & title);

		void SetNumSamples(int numSamples);

		const GLFWwindow & GetWindow() const { return *window; }
		void NewWindow(int windowMode, int video_mode);

		void Update();

		double GetTimeSeconds() const {return glfwGetTime();}
	private:
		int InitWindowingToolkit() const;

		GLFWwindow * window;

		int fbwidth_, fbheight_;	// framebuffer width & height
		int wwidth_, wheight_;		// window width & height

		static void FramebufferSizeCallback(GLFWwindow * window, int width, int height);
		static void WindowPosCallback(GLFWwindow * window, int x, int y);
		static void CursorPosCallback(GLFWwindow * window, double xPos, double yPos);
		static void MouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
		static void MouseScrollCallback(GLFWwindow * window, double xOffset, double yOffset);
		static void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);	//Static function which receives key callbacks from window
		static void CharCallback(GLFWwindow * window, unsigned int codePoint);
	};
}

