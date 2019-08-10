#pragma once

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/GL.h>
#include "OSE-Core/Rendering/RenderingEngine.h"
#include "OSE-Core/EngineDependencies/glm/glm.hpp"
#include "RenderTaskGL.h"
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
		// used to render the game
		// called every game update for every render object in pool
		///template <RenderObjectGL>
		///virtual void update(RenderObjectGL & render_object) override;
		///virtual void update(RenderObjectGL &);

	private:
		//load OpenGL functions using GLEW
		//return of 0 = success, return of -1 = error
		static int InitGlew();

		//the projection matrix, can be a perspective or an orthographic projection matrix
		glm::mat4 projection_matrix_;

		void UpdateOrthographicProjectionMatrix(const int fbwidth, const int fbheight) override;
		void UpdatePerspectiveProjectionMatrix(const float fovyDeg, const int fbwidth, const int fbheight, const float znear, const float zfar) override;

		//TODO - remove test list and replace with render object system
		//std::vector<SpriteRenderer> sprites;
	};
}

