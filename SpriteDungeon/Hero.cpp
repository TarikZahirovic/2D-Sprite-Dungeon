#include "Hero.h"

using namespace SpriteDungeon;

//Initializing the hero sprite
void Hero::initialize(SDL_Renderer* pRenderer, const std::string& filePath1, const std::string& filePath2, float width, float height) {
	size.x = width;
	size.y = height;
	pos2.x = pos.x + width;
	pos2.y = pos.y + height;
	frame1 = loadTexture(pRenderer, filePath1);
	frame2 = loadTexture(pRenderer, filePath2);
	texture = frame1;
	secondsAlive = 0.0f;
}

//Updating hero sprite's movement and animation
void Hero::update(float deltaSeconds, PlayerState& player, WorldState& world) {

	//Health check
	if (player.health <= 0) {
		player.died = true;
		player.won = false;
		player.finishedGame = true;
	}

	//Coin check
	if (player.inventory.size() >= 5) { player.invincible = true; }

	//Invincibility Timer
	if (player.invincible) {
		player.invTime += deltaSeconds;
		if (player.invTime > 30.0f) { player.invincible = false; }
	}

	//Movement Logic
	Vector2d direction(0.0f, 0.0f);
	float speed = 500.0f;

	if (player.movingUp) { direction.y = -1.0f; }
	else if (player.movingDown) { direction.y = 1.0f; }

	if (player.movingRight) { direction.x = 1.0f;}
	else if (player.movingLeft) { direction.x = -1.0f;}

	direction.normalize();

	Vector2d newPos = pos;
	newPos += direction * speed * deltaSeconds;

	if (player.movingRight) {
		if (world.isWalkableTile(newPos, player)) {
			pos = newPos;
		}
	}
	if (player.movingDown) {
		if (world.isWalkableTile(newPos, player)) {
			pos = newPos;
		}
	}
	else {
		if (world.isWalkableTile(newPos, player)) {pos = newPos;}
	}

	world.offset = pos;
	player.pos = pos2 + pos;

	//Animation Logic
	secondsAlive += deltaSeconds;
	if ((int)secondsAlive % 2 == 0) {texture = frame1;}
	else { texture = frame2; }

}