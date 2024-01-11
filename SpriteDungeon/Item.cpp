#include "Item.h"

using namespace SpriteDungeon;

//Initializes item sprites
void Item::initialize(SDL_Renderer* pRenderer, const std::string& filePath1, const std::string& filePath2, float width, float height) {
	size.x = width;
	size.y = height;
	frame1 = loadTexture(pRenderer, filePath1);
	frame2 = loadTexture(pRenderer, filePath2);
	texture = frame1;
	secondsAlive = 0.0f;
}

//Updates item sprites
void Item::update(float deltaSeconds, PlayerState& player, WorldState& world) {

	//Collision Logic
	ItemData& current = world.items[itemIndex];
	if (current.alive) {
		Vector2d toPlayer = (current.pos + Vector2d(66.0f, 69.0f)) - player.pos;
		if (toPlayer.getLength() < 50.0f) {
			if (!enemy) {
				if (!treasure) {
					current.alive = false;
					player.inventory.push_back(current.type);
				}
				else {
					player.finishedGame = true;
					player.won = true;
				}
			}
			else {
				current.alive = false;
				if (!player.invincible) {player.health--;}
			}
		}
	}
	visible = current.alive;

	//Animation Logic
	secondsAlive += deltaSeconds;
	if ((int)secondsAlive % 2 == 0) { texture = frame1; }
	else { texture = frame2; }

}

void Item::render(SDL_Renderer* pRenderer, const PlayerState& player, const WorldState& world, const Vector2d& baseTrans) {
	SDL_Rect destRect = { 
		(int)world.items[itemIndex].pos.x + (int)baseTrans.x,
		(int)world.items[itemIndex].pos.y + (int)baseTrans.y, 
		(int)size.x, (int)size.y 
	};
	if (texture != nullptr && visible) {
		SDL_RenderCopy(pRenderer, texture, nullptr, &destRect);
	}
}

void Item::setIndex(int newIndex) { itemIndex = newIndex; }