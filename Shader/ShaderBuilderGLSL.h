#pragma once
#include "OSE-Core/Shader/ShaderBuilder.h"

namespace ose::shader
{
	class ShaderBuilderGLSL : public ShaderBuilder
	{
	public:
		ShaderBuilderGLSL();
		~ShaderBuilderGLSL();



	private:

		virtual void BuildConstColorNode(NConstColor & node) {}
	};
}

