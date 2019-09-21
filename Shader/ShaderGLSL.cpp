#include "stdafx.h"
#include "ShaderGLSL.h"

namespace ose::shader
{
	ShaderGLSL::ShaderGLSL() : Shader()
	{

	}

	ShaderGLSL::~ShaderGLSL()
	{

	}

	// Build a shader object from a shader graph
	void ShaderGLSL::BuildShaderGraph(ShaderGraph & shader_graph)
	{
		// TODO - Work backwards from output color node
		// Start code in the lowest level shader (fragment)
		// Whenever a node is encountered requiring the higher level, ...
		// ...begin that shader & bridge connection between the two shaders
	}
}
