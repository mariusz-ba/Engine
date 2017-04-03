#include "Texture.h"

namespace engine { namespace graphics {

	Texture::Texture() :
		m_Width(0),
		m_Height(0)
	{
	}

	Texture::Texture(const char* filename)
	{
		loadFromFile(filename);
	}

	Texture::~Texture()
	{
		if (m_TextureID)
			glDeleteTextures(1, &m_TextureID);
	}

	void Texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::loadFromFile(const char* filename)
	{
		//this = ResourceManager::Instance()->LoadTextureFromFile(filename);
		if (m_TextureID)
			glDeleteTextures(1, &m_TextureID);
		load(filename);
	}
	
	void Texture::load(const char* filename)
	{
		//TODO: check image format cause i dont know if i need to use i.e. RGB or RGBA ?
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *dib = nullptr;
		BYTE* bits = nullptr;

		fif = FreeImage_GetFileType(filename, 0);
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);
		if (fif == FIF_UNKNOWN)
			return;

		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		if (!dib)
			return;

		//TODO: set some errors or throw

		bits = FreeImage_GetBits(dib);
		m_Width = FreeImage_GetWidth(dib);
		m_Height = FreeImage_GetHeight(dib);
		m_BitsPerPixel = FreeImage_GetBPP(dib);

		if ((bits == 0) || (m_Width == 0) || (m_Height == 0))
			return;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);

		this->bind();
		// Setup texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);

		// Set texture image data based on the bits per pixel
		switch (m_BitsPerPixel)
		{
		case 24:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, bits);
			break;
		case 32:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, bits);
			break;
		}
		this->unbind();

		FreeImage_Unload(dib);
	}

} }