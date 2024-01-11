#pragma once
#include "Sprite.h"

namespace SpriteDungeon {
	class Hero : public Sprite {
		public:
			virtual void initialize(SDL_Renderer* pRenderer, const std::string& filePath1, const std::string& filePath2,
				float width, float height);
			virtual void update(float deltaSeconds, PlayerState& player, WorldState& world);

		private:
			SDL_Texture* frame1;
			SDL_Texture* frame2;
			float secondsAlive;
	};
}