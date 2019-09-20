#pragma once
#include "OSE-Core/Types.h"
#include "TextureGL.h"
#include "ERenderObjectType.h"

namespace ose::rendering
{
	struct RenderObjectGL
	{
		ERenderObjectType type_;

		// TODO - Implement stride (or something similar) to determine which textures belong to same instance within render object
		std::vector<ose::unowned_ptr<TextureGL const>> textures_;
	};
}
