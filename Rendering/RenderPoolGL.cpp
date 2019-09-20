#include "stdafx.h"
#include "RenderPoolGL.h"

namespace ose::rendering
{
	RenderPoolGL::RenderPoolGL()
	{

	}

	RenderPoolGL::~RenderPoolGL()
	{

	}

	// Add a sprite renderer component to the render pool
	void RenderPoolGL::AddSpriteRenderer(ose::unowned_ptr<SpriteRenderer> sr)
	{
		sps.push_back(sr);
	}
}
