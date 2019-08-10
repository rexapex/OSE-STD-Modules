#include "stdafx.h"
#include "WindowManagerGLFW.h"


namespace ose::windowing
{
	WindowManagerGLFW::WindowManagerGLFW()
	{
		if(InitWindowingToolkit() == -1)
			fprintf(stderr, "Error: %s\n", "Failed to initialise GLFW");
	}

	WindowManagerGLFW::~WindowManagerGLFW()
	{
		if(window)
		{
			glfwDestroyWindow(window);
		}
	}


	static void errorCallback(int error, const char * description)	//Prints error message description to stderr
	{
		fprintf(stderr, "Error: %s\n", description);
	}

	int WindowManagerGLFW::InitWindowingToolkit() const
	{
		glfwSetErrorCallback(errorCallback);

		if(!glfwInit())		/**Initialise GLFW*/
			return -1;		/**Return -1 if failed to initialise*/

		return 0;
	}

	std::vector<VideoMode> WindowManagerGLFW::GetAvailableVideoModes()
	{
		int count;
		const GLFWvidmode * modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
		std::vector<VideoMode> video_modes;

		for(int i = 0; i < count; i++)
		{
			video_modes.emplace_back(modes[i].width, modes[i].height, modes[i].refreshRate);
		}

		return video_modes;
	}

	void WindowManagerGLFW::NewWindow(int window_mode, int video_mode)
	{
		GLFWwindow * window;

		const GLFWvidmode * mode;

		int num_video_modes;
		const GLFWvidmode * modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &num_video_modes);

		if(video_mode >= 0 && video_mode < num_video_modes)
		{
			mode = &modes[video_mode];
		}
		else
		{
			mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		}

		std::cerr << "Resolution: " << mode->width << "x" << mode->height << std::endl;

		switch(window_mode)
		{
		case 0:	//Fullscreen window
		{
			window = glfwCreateWindow(mode->width, mode->height, "Origami Sheep Engine", glfwGetPrimaryMonitor(), NULL);
			break;
		}
		case 1:	//Windowed mode
		{
			window = glfwCreateWindow(mode->width, mode->height, "Origami Sheep Engine", NULL, NULL);
			break;
		}
		case 2:	//Borderless windowed mode
		{
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			window = glfwCreateWindow(mode->width, mode->height, "Origami Sheep Engine", glfwGetPrimaryMonitor(), NULL);
			break;
		}
		default: //Default to fullscreen window
		{
			window = glfwCreateWindow(mode->width, mode->height, "Origami Sheep Engine", glfwGetPrimaryMonitor(), NULL);
			break;
		}
		}

		//if there is a window already, destroy it
		if(this->window)
		{
			glfwDestroyWindow(this->window);
			this->window = nullptr;
		}

		if(!window)
		{
			fprintf(stderr, "Error: %s\n", "Failed to create GLFW window");
		}
		else
		{
			glfwGetFramebufferSize(window, &fbwidth_, &fbheight_);	//set the initial framebuffer width and height
			glfwGetWindowSize(window, &wwidth_, &wheight_);
			glfwSetWindowUserPointer(window, this);		//Set the window pointer to be this InputManager for later use
			glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
			glfwSetKeyCallback(window, KeyCallback);	//Set callbacks
			//glfwSetWindowPosCallback(window, windowPosCallback);
			//glfwSetCursorPosCallback(window, cursorPosCallback);
			glfwSetMouseButtonCallback(window, MouseButtonCallback);
			//glfwSetScrollCallback(window, mouseScrollCallback);
			//glfwSetCharCallback(window, charCallback);

			std::cerr << "Created GLFW Window" << std::endl;

			glfwMakeContextCurrent(window);
			if(!glfwGetCurrentContext())
			{
				std::cerr << "Failed to make context current" << std::endl;
			}
			else
			{
				std::cerr << "Set window to be default render context" << std::endl;
			}

			this->window = window;
		}
	}



	void WindowManagerGLFW::Update()
	{
		//swap buffers to update the screen and then poll for new events
		glfwSwapBuffers(window);
		glfwPollEvents();

		//check if game should be closed
		if(glfwWindowShouldClose(window))
		{
			glfwDestroyWindow(window);
			window = nullptr;
			exit(0);
		}

		//std::cerr << "HOW!?!?!?\n";
		//double xpos, ypos;
		//glfwGetCursorPos(window, &xpos, &ypos);		//Callback function not called frequently enough to update camera
		//inputManager->cursorPosCallbackImpl(xpos, ypos);
	}




	void WindowManagerGLFW::SetTitle(const std::string & title)
	{
		glfwSetWindowTitle(window, title.c_str());
	}




	int WindowManagerGLFW::SetMouseVisibility(int value)
	{
		if(value == 0)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else if(value == 1)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		else if(value == 2)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return 0;
	}



	void WindowManagerGLFW::SetWindowSize(int width, int height)
	{
		glfwSetWindowSize(window, width, height);
	}

	void WindowManagerGLFW::SetWindowPos(int x, int y)
	{
		glfwSetWindowPos(window, x, y);
	}



	void WindowManagerGLFW::SetNumSamples(int numSamples)
	{

	}



	void WindowManagerGLFW::FramebufferSizeCallback(GLFWwindow * window, int width, int height)
	{
		WindowManagerGLFW * windowManager = reinterpret_cast<WindowManagerGLFW *>(glfwGetWindowUserPointer(window));
		windowManager->fbwidth_ = width;
		windowManager->fbheight_ = height;
		windowManager->FramebufferSizeCallbackImpl(width, height);
	}

	void WindowManagerGLFW::WindowPosCallback(GLFWwindow * window, int x, int y)
	{
		WindowManagerGLFW * windowManager = reinterpret_cast<WindowManagerGLFW *>(glfwGetWindowUserPointer(window));	//Get the window user pointer
		windowManager->WindowPosCallbackImpl(x, y);
	}

	void WindowManagerGLFW::CursorPosCallback(GLFWwindow * window, double xPos, double yPos)
	{
		WindowManagerGLFW * windowManager = reinterpret_cast<WindowManagerGLFW *>(glfwGetWindowUserPointer(window));	//Get the window user pointer
		windowManager->CursorPosCallbackImpl(xPos, yPos);		//Forward the callback to the member implementation method
	}

	void WindowManagerGLFW::MouseButtonCallback(GLFWwindow * window, int button, int action, int mods)
	{
		WindowManagerGLFW * windowManager = reinterpret_cast<WindowManagerGLFW *>(glfwGetWindowUserPointer(window));	//Get the window user pointer
		windowManager->MouseButtonCallbackImpl(button, action, mods);		//Forward the callback to the member implementation method
	}

	void WindowManagerGLFW::MouseScrollCallback(GLFWwindow * window, double xOffset, double yOffset)
	{
		WindowManagerGLFW * inputManager = reinterpret_cast<WindowManagerGLFW *>(glfwGetWindowUserPointer(window));	//Get the window user pointer
		inputManager->MouseScrollCallbackImpl(xOffset, yOffset);		//Forward the callback to the member implementation method
	}

	void WindowManagerGLFW::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)	//Receives input from the window
	{
		WindowManagerGLFW * windowManager = reinterpret_cast<WindowManagerGLFW *>(glfwGetWindowUserPointer(window));	//Get the window user pointer
		windowManager->KeyCallbackImpl(key, scancode, action, mods);		//Forward the callback to the member implementation method
	}

	void WindowManagerGLFW::CharCallback(GLFWwindow * window, unsigned int codePoint)
	{
		WindowManagerGLFW * windowManager = reinterpret_cast<WindowManagerGLFW *>(glfwGetWindowUserPointer(window));	//Get the window user pointer
		windowManager->CharCallbackImpl(codePoint);								//Forward the callback to the member implementation method
	}
}
