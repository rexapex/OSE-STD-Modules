#pragma once

#define GLEW_STATIC

#include "../../stdafx.h"
#include "../../OSE-Core/Windowing/WindowManager.h"
#include "../../OSE-Core/Rendering/VideoMode.h"
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

		const int getFramebufferWidth() const { return fbwidth_; }
		const int getFramebufferHeight() const { return fbheight_; }

		std::vector<VideoMode> getAvailableVideoModes();

		int	setMouseVisibility(int value);

		void setWindowSize(int width, int height);
		void setWindowPos(int x, int y);

		void setTitle(const std::string & title);

		void setNumSamples(int numSamples);

		//void *  get_window() const;
		void createWindow(int windowMode, int video_mode);

		void update();

		double getTimeSeconds() const {return glfwGetTime();}
	private:
		int initWindowingToolkit() const;

		GLFWwindow * window;

		int fbwidth_, fbheight_;

		static void framebufferSizeCallback(GLFWwindow * window, int width, int height);
		static void windowPosCallback(GLFWwindow * window, int x, int y);
		static void cursorPosCallback(GLFWwindow * window, double xPos, double yPos);
		static void mouseButtonCallback(GLFWwindow * window, int button, int action, int mods);
		static void mouseScrollCallback(GLFWwindow * window, double xOffset, double yOffset);
		static void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods);	//Static function which receives key callbacks from window
		static void charCallback(GLFWwindow * window, unsigned int codePoint);
	};
}

