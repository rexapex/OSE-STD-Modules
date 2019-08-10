#pragma once
#include "OSE-Core/Rendering/RenderTask.h"
#include "OSE-Core/Entity/SpriteRenderer.h"
#include <GL/GL.h>

namespace ose::rendering
{
	using namespace entity;

	class RenderTaskGL : public RenderTask
	{
	public:
		RenderTaskGL();
		~RenderTaskGL() noexcept;
		RenderTaskGL(RenderTaskGL & other);
		RenderTaskGL & operator=(RenderTaskGL & other);
		RenderTaskGL(RenderTaskGL && other);
		RenderTaskGL & operator=(RenderTaskGL && other);

		uint32_t gl_tex_id_ { 0 };
	public:
		// initialise the render object to render sprite renderer data
		// IMPORTANT - can only be called from thread containing the render context
		void Init(SpriteRenderer * sprite_renderer) override;

		// render the OpenGL draw data to the screen
		void Update() override;
	};
}
