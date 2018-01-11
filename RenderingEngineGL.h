#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/GL.h>
#include "../stdafx.h"
#include "../RenderingEngine.h"
#include "../EngineDependencies/glm/glm.hpp"

namespace origami_sheep_engine
{
	class RenderingEngineGL : public RenderingEngine
	{
	public:
		RenderingEngineGL();
		virtual ~RenderingEngineGL();

		virtual void render();

	private:
		//load OpenGL functions using GLEW
		//return of 0 = success, return of -1 = error
		static int initGLEW();

		//the projection matrix, can be a perspective or an orthographic projection matrix
		glm::mat4 projection_matrix_;

		void updateOrthographicProjectionMatrix(const int fbwidth, const int fbheight) override;
		void updatePerspectiveProjectionMatrix(const float fovyDeg, const int fbwidth, const int fbheight, const float znear, const float zfar) override;
	};
}

