#pragma once
#include "SDL.h"
#include "GameCore.h"
#include <string>
#include <vector>

namespace SpriteDungeon {
	class Sprite {
		public :
			Sprite();

			Vector2d pos;
			Vector2d pos2;
			Vector2d size;
			bool visible;

			virtual void initialize(SDL_Renderer* pRenderer, const std::string& filePath, float width, float height);
			virtual void update(float deltaSeconds, PlayerState& player, WorldState& world);
			virtual void render(SDL_Renderer* pRenderer, const PlayerState& player, const WorldState& world, const Vector2d& baseTrans);
			virtual void cleanup();
			static void cleanupTextures();
		
		protected:
			SDL_Texture* texture;

			static SDL_Texture* loadTexture(SDL_Renderer* pRenderer, const std::string& filePath);

			struct LoadedTexture {
				std::string filename;
				SDL_Texture* textureCheck;
			};

			static std::vector<LoadedTexture> s_LoadedTextures;
	};
}