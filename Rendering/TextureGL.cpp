#include "stdafx.h"
#include "TextureGL.h"
#include <GL/GL.h>

namespace ose::rendering
{
	// bind the texture ready for rendering
	void TextureGL::bind()
	{
		glBindTexture(GL_TEXTURE_2D, gl_tex_id_);
	}

	// create the texture in GPU memory
	// IMPORTANT - cannot be called from constructor since the ResourceLoader is multithreaded but the rendering context is not
	void TextureGL::createTexture()
	{
		// first, make sure any existing texture is freed
		destroyTexture();

		// then, create the new OpenGL texture
		glGenTextures(1, &gl_tex_id_);

		// set the contents of the texture
		bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data_);

		// TODO - add support for Anisotropic filtering
		// set min filter mode
		switch(meta_data_.min_filter_mode_)
		{
		case ETextureFilterMode::NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
		case ETextureFilterMode::LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case ETextureFilterMode::LINEAR_MIPMAP_NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			break;
		case ETextureFilterMode::LINEAR_MIPMAP_LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;
		case ETextureFilterMode::NEAREST_MIPMAP_NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			break;
		case ETextureFilterMode::NEAREST_MIPMAP_LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			break;
		}

		// TODO - add support for Anisotropic filtering
		// set mag filter mode
		switch(meta_data_.mag_filter_mode_)
		{
		case ETextureFilterMode::NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		case ETextureFilterMode::LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case ETextureFilterMode::LINEAR_MIPMAP_NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			break;
		case ETextureFilterMode::LINEAR_MIPMAP_LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			break;
		case ETextureFilterMode::NEAREST_MIPMAP_NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			break;
		case ETextureFilterMode::NEAREST_MIPMAP_LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			break;
		}

		if(meta_data_.mip_mapping_enabled_) {
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}

	// free the texture from GPU memory
	// IMPORTANT - cannot be called from destructor since the ResourceManager is multithreaded but the rendering context is not
	// IMPORTANT - failure to call this may result in GPU memory leaks
	void TextureGL::destroyTexture()
	{
		// check that the gl_tex_id_ is valid
		if(gl_tex_id_ != 0)
		{
			// if it is valid, free it then set the variable to 0
			glDeleteTextures(1, &gl_tex_id_);
			gl_tex_id_ = 0;
		}
	}
}
