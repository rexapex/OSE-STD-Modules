#pragma once
#include "OSE-Core/Rendering/RenderObject.h"
#include "OSE-Core/Entity/SpriteRenderer.h"
#include <GL/GL.h>

namespace ose::rendering
{
	using namespace entity;

	class RenderObjectGL : public RenderObject
	{
	public:
		RenderObjectGL();
		~RenderObjectGL() noexcept;
		RenderObjectGL(RenderObjectGL & other);
		RenderObjectGL & operator=(RenderObjectGL & other);
		RenderObjectGL(RenderObjectGL && other);
		RenderObjectGL & operator=(RenderObjectGL && other);

		uint32_t gl_tex_id_ { 0 };
	public:
		// initialise the render object to render sprite renderer data
		// IMPORTANT - can only be called from thread containing the render context
		void init(SpriteRenderer * sprite_renderer) override;
	};
}
