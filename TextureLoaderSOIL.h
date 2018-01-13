#pragma once
#include "../stdafx.h"
#include "../TextureLoader.h"
#include "../Texture.h"
#include <SOIL.h>

namespace origami_sheep_engine
{
	class TextureLoaderSOIL : TextureLoader
	{
	public:
		TextureLoaderSOIL(const std::string & project_path);
		~TextureLoaderSOIL();
		//TextureLoader is NOT copyable
		TextureLoaderSOIL(TextureLoaderSOIL &) = delete;
		TextureLoaderSOIL & operator=(TextureLoaderSOIL &) = delete;
		//TextureLoader IS movable
		TextureLoaderSOIL(TextureLoaderSOIL &&) noexcept = default;
		TextureLoaderSOIL & operator=(TextureLoaderSOIL &&) noexcept = default;

	private:
		//loads the texture and sets the values of img_data, width and height
		//path is absolute and is guaranteed to exist
		virtual void loadTexture(const std::string & path, IMGDATA img_data, int32_t * width, int32_t * height);

		//free resources used by the texture (img_data)
		virtual void freeTexture(const Texture & tex);
	};
}

