#pragma once
#include "OSE-Core/Shader/Shader.h"

namespace ose::shader
{
	class ShaderGLSL : public Shader
	{
	public:
		ShaderGLSL();
		virtual ~ShaderGLSL();

		// Build a shader object from a shader graph
		virtual void BuildShaderGraph(ShaderGraph & shader_graph);
	};
}

