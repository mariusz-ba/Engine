#include "ResourceManager.h"

namespace engine {

	ResourceManager* ResourceManager::m_ResourceManager(nullptr);

	ResourceManager* ResourceManager::Instance()
	{
		if(!m_ResourceManager)
			m_ResourceManager = new ResourceManager();
		return m_ResourceManager;
	}

	ResourceManager::ResourceManager()
	{
		FreeImage_Initialise();
	}

	ResourceManager::~ResourceManager()
	{
		FreeImage_DeInitialise();
		UnloadAllTextures();
	}

	graphics::Texture* ResourceManager::LoadTextureFromFile(const char* filepath)
	{
		if (m_Textures.count(filepath)) {
			return m_Textures.at(filepath);
		}

		graphics::Texture* texture = new graphics::Texture();

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		BYTE* bits = nullptr;

		fif = FreeImage_GetFileType(filepath, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filepath);
		if (fif == FIF_UNKNOWN)
			return nullptr;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filepath);
		if (!dib)
			return nullptr;

		bits = FreeImage_GetBits(dib);
		GLuint textureID;
		unsigned int width = FreeImage_GetWidth(dib);
		unsigned int height = FreeImage_GetHeight(dib);
		unsigned int bpp = FreeImage_GetBPP(dib);

		if ((bits == 0) || (width == 0) || (height == 0))
			return nullptr;

		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);

		texture->setTextureID(textureID);
		texture->setWidth(width);
		texture->setHeight(height);
		texture->setBitsPerPixel(bpp);

		texture->bind();
		// Setup texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

		// Set texture image data based on the bits per pixel
		switch (bpp)
		{
		case 24:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
			break;
		case 32:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
			break;
		}
		texture->unbind();

		FreeImage_Unload(dib);

		m_Textures[filepath] = texture;
		return texture;
	}

	void ResourceManager::UnloadTexture(const char* filepath)
	{
		if (m_Textures.count(filepath)) {
			delete m_Textures[filepath];
			m_Textures.erase(filepath);
		}
	}

	void ResourceManager::UnloadTexture(graphics::Texture* texture)
	{
		for (auto it = m_Textures.begin(); it != m_Textures.end(); ++it)
		{
			if (it->second == texture)
				UnloadTexture(it->first);
		}
	}

	void ResourceManager::UnloadAllTextures()
	{
		for (auto it = m_Textures.begin(); it != m_Textures.end(); ++it)
			delete it->second;
		m_Textures.clear();
	}

}