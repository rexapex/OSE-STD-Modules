#include "../../stdafx.h"
#include "RenderingEngineGL.h"

namespace ose::rendering
{
	RenderingEngineGL::RenderingEngineGL() : RenderingEngine()
	{
		initGLEW();
	}

	RenderingEngineGL::~RenderingEngineGL() {}

	void RenderingEngineGL::updateOrthographicProjectionMatrix(const int fbwidth, const int fbheight)
	{
		DEBUG_LOG("updating othographic projection matrix");
		float aspect_ratio = (float)fbwidth/(float)fbheight;
		//setting glOrtho and glViewport in the following ways worked in testing
		projection_matrix_ = glm::ortho(-(float)fbwidth/2 * aspect_ratio, (float)fbwidth/2 * aspect_ratio, -(float)fbheight/2 * aspect_ratio, (float)fbheight/2 * aspect_ratio);
		glViewport(0, 0, fbwidth, fbheight);
	}

	void RenderingEngineGL::updatePerspectiveProjectionMatrix(const float fovyDeg, const int fbwidth, const int fbheight, const float znear, const float zfar)
	{
		DEBUG_LOG("updating perspective projection matrix");
		projection_matrix_ = glm::perspective(glm::radians(fovyDeg), (float)fbwidth/(float)fbheight, znear, zfar);	//TODO - test aspect ratio is correct for a variety of resolutions
		glViewport(0, 0, fbwidth, fbheight);	//still required with shaders as far as I'm aware
	}

	//add entities render components to render objects
	void RenderingEngineGL::addEntityRenderObject(std::vector<Entity> & entities)
	{
		//for(Entity & e : entities)
		{
			//for(std::unique_ptr<SpriteRenderer> & r : e.get_components())
			{

			}
		}
	}

	//clear the list of entity render object
	void RenderingEngineGL::clearEntityRenderObjects(const Entity & entity)
	{

	}

	void RenderingEngineGL::render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glLoadIdentity();
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f,   1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(1.0f,  -1.0f);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-1.0f, -1.0f);
		glEnd();
	}

	//create a rendering engine specific texture object for a ose texture object
	void RenderingEngineGL::createTexture(const Texture & texture)
	{
	}

	//delete a rendering engine specific texture object
	void RenderingEngineGL::deleteTexture(const Texture & texture)
	{
	}

	//load OpenGL functions using GLEW
	//return of 0 = success, return of -1 = error
	int RenderingEngineGL::initGLEW()
	{
		GLenum err = glewInit();
		if(GLEW_OK != err)
		{
			//GLEW Initialisation failed
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
			return -1;		//return with error
		}
		fprintf(stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

		std::cerr << "Initialised GLEW" << std::endl;
		if(GLEW_VERSION_3_2)
		{
			std::cerr << "OpenGL 3.2 Supported" << std::endl;
		}
		else
		{
			std::cerr << "OpenGL 3.2 Not Supported" << std::endl;

			if(GLEW_ARB_instanced_arrays)
			{
				std::cerr << "Instanced Arrays Available" << std::endl;
			}
			else
			{
				std::cerr << "Instanced Arrays Not Supported" << std::endl;
			}
		}

		return 0;			//return with success
	}
}
