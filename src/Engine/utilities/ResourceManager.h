#pragma once

#include <map>
#include "FreeImage.h"
#include "../graphics/Texture.h"

//TODO: don't use texture manager directly!

namespace engine {

	class ResourceManager {
	public:
		static ResourceManager* Instance();
		virtual ~ResourceManager();

		graphics::Texture* LoadTextureFromFile(const char* filepath);
		void UnloadTexture(const char* filepath);
		void UnloadTexture(graphics::Texture* texture);
		void UnloadAllTextures();

	protected:
		ResourceManager();
		ResourceManager(const ResourceManager& other);
		ResourceManager& operator=(const ResourceManager& other);

		static ResourceManager* m_ResourceManager;

		std::map<const char*, graphics::Texture*> m_Textures;
	};

}