#include "stdafx.h"
#include "ModelLoaderASSIMP.h"

namespace ose::resources
{
	ModelLoaderASSIMP::ModelLoaderASSIMP(const std::string & project_path) : ModelLoader(project_path)
	{
		// Create an instance of the Importer class
		Assimp::Importer importer;
	}

	ModelLoaderASSIMP::~ModelLoaderASSIMP()
	{
	}
}
