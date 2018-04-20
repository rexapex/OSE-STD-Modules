#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/GL.h>
#include "../../stdafx.h"
#include "../../OSE-Core/Rendering/RenderingEngine.h"
#include "../../OSE-Core/Rendering/SpriteRenderer.h"
#include "../../OSE-Core/EngineDependencies/glm/glm.hpp"

namespace ose::rendering
{
	using namespace game;

	class RenderingEngineGL : public RenderingEngine
	{
	public:
		RenderingEngineGL();
		virtual ~RenderingEngineGL();

		virtual void render();

		//add entities render components to render objects
		virtual void addEntityRenderObject(std::vector<Entity> & entities);

		//clear the list of entity render object
		virtual void clearEntityRenderObjects(const Entity & entity);

	private:
		//load OpenGL functions using GLEW
		//return of 0 = success, return of -1 = error
		static int initGLEW();

		//the projection matrix, can be a perspective or an orthographic projection matrix
		glm::mat4 projection_matrix_;

		void updateOrthographicProjectionMatrix(const int fbwidth, const int fbheight) override;
		void updatePerspectiveProjectionMatrix(const float fovyDeg, const int fbwidth, const int fbheight, const float znear, const float zfar) override;

		//create a rendering engine specific texture object for a ose texture object
		void createTexture(const Texture & texture) override;

		//delete a rendering engine specific texture object
		void deleteTexture(const Texture & texture) override;

		//TODO - remove test list and replace with render object system
		std::vector<SpriteRenderer> sprites;
	};
}

