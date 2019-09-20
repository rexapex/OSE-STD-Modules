#include "stdafx.h"
#include "RenderPoolGL.h"
#include "ERenderObjectType.h"

namespace ose::rendering
{
	RenderPoolGL::RenderPoolGL()
	{
		// TODO - Replace this with proper render & shader group pass system
		render_passes_.emplace_back();
		render_passes_[0].shader_groups_.emplace_back();
	}

	RenderPoolGL::~RenderPoolGL()
	{

	}

	// Add a sprite renderer component to the render pool
	void RenderPoolGL::AddSpriteRenderer(ose::unowned_ptr<SpriteRenderer> sr)
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
			}
		}
		// If the sprite renderer group could not be found, make one
		if(!found_sprite_renderer_group)
		{
			s.render_objects_.emplace_back();
			s.render_objects_.back().type_ = ERenderObjectType::SPRITE_RENDERER;
			s.render_objects_.back().textures_.emplace_back(static_cast<ose::unowned_ptr<TextureGL const>>(sr->GetTexture()));
		}
	}
}
