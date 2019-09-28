#pragma once
#include "OSE-Core/Types.h"
#include "TextureGL.h"
#include "ERenderObjectType.h"

namespace ose::rendering
{
	struct RenderObjectGL
	{
		ERenderObjectType type_;

		GLuint vbo_;
		GLuint vao_;

		// TODO - Implement stride (or something similar) to determine which textures belong to same instance within render object
		std::vector<ose::unowned_ptr<TextureGL const>> textures_;

		// TODO - Experiment with handling transforms differently
		// TODO - Replace with pointer to glm::mat4 s.t. changes made to entity transform immediately have effect on render object
		std::vector<glm::mat4> transforms_;
	};
}
