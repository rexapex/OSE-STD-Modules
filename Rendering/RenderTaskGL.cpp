#include "stdafx.h"
#include "RenderTaskGL.h"

namespace ose::rendering
{
	RenderTaskGL::RenderTaskGL() {}
	RenderTaskGL::~RenderTaskGL() noexcept {}

	RenderTaskGL::RenderTaskGL(RenderTaskGL & other) : gl_tex_id_(other.gl_tex_id_) {}

	RenderTaskGL & RenderTaskGL::operator=(RenderTaskGL & other)
	{
		gl_tex_id_ = other.gl_tex_id_;
		return *this;
	}

	RenderTaskGL::RenderTaskGL(RenderTaskGL && other) : gl_tex_id_(std::move(other.gl_tex_id_)) {}

	RenderTaskGL & RenderTaskGL::operator=(RenderTaskGL && other)
	{
		gl_tex_id_ = std::move(other.gl_tex_id_);
		return *this;
	}

	// initialise the render object to render sprite renderer data
	// IMPORTANT - can only be called from thread containing the render context
	void RenderTaskGL::Init(SpriteRenderer * sprite_renderer)
	{
		// since the OpenGL render engine is being used, assume the texture is a TextureGL (otherwise it wouldn't work anyway)
		const TextureGL * gl_tex = static_cast<const TextureGL *>(sprite_renderer->GetTexture());
		// set the gl_tex_id
		this->gl_tex_id_ = gl_tex ? gl_tex->GetGlTexId() : 0;
	}

	// render the OpenGL draw data to the screen
	void RenderTaskGL::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glEnable(GL_TEXTURE_2D);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glLoadIdentity();
		glBindTexture(GL_TEXTURE_2D, this->gl_tex_id_);
		//DEBUG_LOG(render_object.gl_tex_id_);
		glBegin(GL_QUADS);
		glTexCoord2i(1, 0);   glVertex2f(-0.5f,   0.5f);
		glTexCoord2i(1, 1);   glVertex2f(-0.5f,  -0.5f);
		glTexCoord2i(0, 1);   glVertex2f(0.5f, -0.5f);
		glTexCoord2i(0, 0);   glVertex2f(0.5f, 0.5f);
		glEnd();
	}
}
