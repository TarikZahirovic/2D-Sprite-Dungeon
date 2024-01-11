#pragma once
#include "Sprite.h"

namespace SpriteDungeon {
	class RoomRenderer : public Sprite {
		public:
			virtual void initialize(SDL_Renderer* pRenderer, const std::string& filePath1, const std::string& filePath2);
			virtual void render(SDL_Renderer* pRenderer, const PlayerState& player, const WorldState& world, const Vector2d& baseTrans);

		private:
			SDL_Texture* floor;
			SDL_Texture* wall;
	};
}