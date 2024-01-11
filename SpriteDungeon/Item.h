#pragma once
#include "Sprite.h"

namespace SpriteDungeon {
	class Item : public Sprite {
		public:
			bool enemy;
			bool treasure;
			virtual void initialize(SDL_Renderer* pRenderer, const std::string& filePath1, const std::string& filePath2,
				float width, float height);
			virtual void update(float deltaSeconds, PlayerState& player, WorldState& world);
			virtual void render(SDL_Renderer* pRenderer, const PlayerState& player, const WorldState& world, const Vector2d& baseTrans);
			void setIndex(int newIndex);

		private:
			int itemIndex;
			SDL_Texture* frame1;
			SDL_Texture* frame2;
			float secondsAlive;
	};
}
