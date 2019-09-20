#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/GL.h>
#include "OSE-Core/Rendering/RenderingEngine.h"
#include "OSE-Core/EngineDependencies/glm/glm.hpp"
#include "RenderPoolGL.h"
#include "TextureGL.h"

namespace ose::rendering
{
	using namespace game;

	class RenderingEngineGL : public RenderingEngine
	{
	public:
		RenderingEngineGL();
		virtual ~RenderingEngineGL();

		// Engine::update method overriden
		// Called every game update to render all object in the pool
		virtual void Update();

		// Get a reference to the render pool, s.t. new render objects can be added
		virtual RenderPool & GetRenderPool() { return render_pool_; }
		
	private:
		// Load OpenGL functions using GLEW
		// Return of 0 = success, return of -1 = error
		static int InitGlew();

		// The projection matrix, can be a perspective or an orthographic projection matrix
		glm::mat4 projection_matrix_;

		// The pool of object rendered each engine update
		RenderPoolGL render_pool_;

		// Child functions to update the projection matrix to either orthographic or perspective
		void UpdateOrthographicProjectionMatrix(const int fbwidth, const int fbheight) override;
		void UpdatePerspectiveProjectionMatrix(const float fovyDeg, const int fbwidth, const int fbheight, const float znear, const float zfar) override;
	};
}

