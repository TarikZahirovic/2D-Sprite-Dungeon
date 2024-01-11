#pragma once
#include "Sprite.h"

namespace SpriteDungeon {
	class HUD : public Sprite {
	public:
		bool hp;
		virtual void initialize(
			SDL_Renderer* pRenderer, 
			const std::string& filePath1, 
			const std::string& filePath2,
			const std::string& filePath3,
			const std::string& filePath4,
			const std::string& filePath5,
			const std::string& filePath6,
			float width, float height);
		virtual void update(float deltaSeconds, PlayerState& player, WorldState& world);

	private:
		SDL_Texture* frame1;
		SDL_Texture* frame2;
		SDL_Texture* frame3;
		SDL_Texture* frame4;
		SDL_Texture* frame5;
		SDL_Texture* frame6;
	};
}