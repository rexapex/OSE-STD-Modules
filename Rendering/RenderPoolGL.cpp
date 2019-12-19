#include "stdafx.h"
#include "RenderPoolGL.h"
#include "ERenderObjectType.h"

#include "OSE-Core/EngineReferences.h"

#include "OSE-Core/Math/ITransform.h"
#include "OSE-Core/Entity/SpriteRenderer.h"

// TODO - Remove
#include "OSE-Core/Shader/Shaders/ShaderGraphDefault.h"
#include "ShaderGroupGL.h"

using namespace ose::entity;
using namespace ose::math;

namespace ose::rendering
{
	RenderPoolGL::RenderPoolGL()
	{
		
	}

	RenderPoolGL::~RenderPoolGL()
	{

	}

	// Initialise the render pool
	void RenderPoolGL::Init()
	{
		// TODO - Replace this with proper render pass & shader group system
		std::unique_ptr<ShaderProg> shader_prog_generic = ShaderProgFactories[0]();
		ose::unowned_ptr<ShaderProgGLSL> shader_prog = dynamic_cast<ose::unowned_ptr<ShaderProgGLSL>>(shader_prog_generic.get());
		if(shader_prog)
		{
			ShaderGraphDefault sgd;
			shader_prog->BuildShaderGraph(sgd);
			render_passes_.emplace_back();
			ShaderGroupGL sg;
			sg.shader_prog_ = shader_prog->GetShaderProgId();
			render_passes_[0].shader_groups_.push_back(sg);
		}
	}

	// Add a sprite renderer component to the render pool
	void RenderPoolGL::AddSpriteRenderer(ITransform const & t, ose::unowned_ptr<SpriteRenderer> sr)
	{
		// Try to find a render object the 
		ShaderGroupGL & s = render_passes_[0].shader_groups_[0];
		bool found_sprite_renderer_group { false };
		for(auto & r : s.render_objects_)
		{
			if(r.type_ == ERenderObjectType::SPRITE_RENDERER)
			{
				// Add the sprite renderer to the existing render object
				found_sprite_renderer_group = true;
				r.textures_.push_back(static_cast<ose::unowned_ptr<TextureGL const>>(sr->GetTexture()));
				s.render_objects_.back().transforms_.push_back(t.GetTransformMatrix());
			}
		}
		// If the sprite renderer group could not be found, make one
		if(!found_sprite_renderer_group)
		{
			// Create a VBO for the render object
			GLuint vbo;
			glGenBuffers(1, &vbo);
			// Data consists of 2-float position and 2-float tex coords interleaved
			float data[] = {
				0, 0, 0, 1,
				0, 1, 0, 0,
				1, 1, 1, 0,
				1, 0, 1, 1
			};
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

			// Create a VAO for the render object
			GLuint vao;
			glGenBuffers(1, &vao);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			// TODO - Vertex attrib locations are to be controlled by the built shader program
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (GLvoid*)(2 * sizeof(float)));

			s.render_objects_.emplace_back();
			s.render_objects_.back().vbo_ = vbo;
			s.render_objects_.back().vao_ = vao;
			s.render_objects_.back().type_ = ERenderObjectType::SPRITE_RENDERER;
			s.render_objects_.back().textures_.push_back(static_cast<ose::unowned_ptr<TextureGL const>>(sr->GetTexture()));
			s.render_objects_.back().transforms_.push_back(t.GetTransformMatrix());
		}
	}
}
