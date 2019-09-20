#pragma once
#include "OSE-Core/Rendering/RenderPool.h"

namespace ose::rendering
{
	class RenderPoolGL : public RenderPool
	{
	public:
		RenderPoolGL();
		~RenderPoolGL();

		// Add a sprite renderer component to the render pool
		virtual void AddSpriteRenderer(ose::unowned_ptr<SpriteRenderer> sr);

		std::vector<ose::unowned_ptr<SpriteRenderer>> sps;
	};
}

