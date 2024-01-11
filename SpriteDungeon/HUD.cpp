#include "HUD.h"

using namespace SpriteDungeon;

//Initializes item sprites
void HUD::initialize(SDL_Renderer* pRenderer, 
	const std::string& filePath1, 
	const std::string& filePath2,
	const std::string& filePath3,
	const std::string& filePath4,
	const std::string& filePath5,
	const std::string& filePath6,
	float width, float height) {
	size.x = width;
	size.y = height;
	frame1 = loadTexture(pRenderer, filePath1);
	frame2 = loadTexture(pRenderer, filePath2);
	frame3 = loadTexture(pRenderer, filePath3);
	frame4 = loadTexture(pRenderer, filePath4);
	frame5 = loadTexture(pRenderer, filePath5);
	frame6 = loadTexture(pRenderer, filePath6);
	texture = frame1;
}

//Updates item sprites
void HUD::update(float deltaSeconds, PlayerState& player, WorldState& world) {

	if (hp) {
		switch (player.health) {
			case 0:
				texture = frame4;
				break;
			case 1:
				texture = frame3;
				break;
			case 2:
				texture = frame2;
				break;
			case 3:
			default:
				texture = frame1;
		}
	}
	else {
		switch (player.inventory.size()) {
			case 0:
			default:
				texture = frame1;
				break;
			case 1:
				texture = frame2;
				break;
			case 2:
				texture = frame3;
				break;
			case 3:
				texture = frame4;
				break;
			case 4:
				texture = frame5;
				break;
			case 5:
				texture = frame6;
		}
	}
}