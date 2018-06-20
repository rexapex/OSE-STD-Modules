#include "stdafx.h"
#include "RenderObjectGL.h"

namespace ose::rendering
{
	RenderObjectGL::RenderObjectGL() {}
	RenderObjectGL::~RenderObjectGL() noexcept {}

	RenderObjectGL::RenderObjectGL(RenderObjectGL & other) : gl_tex_id_(other.gl_tex_id_) {}

	RenderObjectGL & RenderObjectGL::operator=(RenderObjectGL & other)
	{
		gl_tex_id_ = other.gl_tex_id_;
		return *this;
	}

	RenderObjectGL::RenderObjectGL(RenderObjectGL && other) : gl_tex_id_(std::move(other.gl_tex_id_)) {}

	RenderObjectGL & RenderObjectGL::operator=(RenderObjectGL && other)
	{
		gl_tex_id_ = std::move(other.gl_tex_id_);
		return *this;
	}

	// initialise the render object to render sprite renderer data
	// IMPORTANT - can only be called from thread containing the render context
	void RenderObjectGL::init(SpriteRenderer * sprite_renderer)
	{
		// since the OpenGL render engine is being used, assume the texture is a TextureGL (otherwise it wouldn't work anyway)
		const TextureGL * gl_tex = static_cast<const TextureGL *>(sprite_renderer->get_texture());
		// set the gl_tex_id
		this->gl_tex_id_ = gl_tex ? gl_tex->get_gl_tex_id() : 0;
	}
}
