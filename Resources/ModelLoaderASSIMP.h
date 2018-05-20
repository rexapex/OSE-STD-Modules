#pragma once

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include "OSE-Core/Resources/ModelLoader.h"

namespace ose::resources
{
	class ModelLoaderASSIMP : public ModelLoader
	{
	public:
		ModelLoaderASSIMP(const std::string & project_path);
		~ModelLoaderASSIMP();
		//ModelLoaderASSIMP is NOT copyable
		ModelLoaderASSIMP(ModelLoaderASSIMP &) = delete;
		ModelLoaderASSIMP & operator=(ModelLoaderASSIMP &) = delete;
		//ModelLoaderASSIMP IS movable
		ModelLoaderASSIMP(ModelLoaderASSIMP &&) noexcept = default;
		ModelLoaderASSIMP & operator=(ModelLoaderASSIMP &&) noexcept = default;
	};
}

