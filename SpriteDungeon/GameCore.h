#pragma once
#include "SDL.h"
#include <string>
#include <vector>

namespace SpriteDungeon {

	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

	struct Vector2d {
		float x;
		float y;

		Vector2d() :
			x(0.0f),
			y(0.0f)
		{

		}

		Vector2d(float inX, float inY) :
			x(inX),
			y(inY)
		{

		}

		bool operator==(const Vector2d& position) const {
			return x == position.x && y == position.y;
		}

		bool operator!=(const Vector2d& position) const {
			return !(*this == position);
		}

		Vector2d& operator+=(const Vector2d& rhs) {
			this->x += rhs.x;
			this->y += rhs.y;
			return *this;
		}

		const Vector2d operator+(const Vector2d& rhs) const {
			return Vector2d(*this) += rhs;
		}

		Vector2d& operator-=(const Vector2d& rhs) {
			this->x -= rhs.x;
			this->y -= rhs.y;
			return *this;
		}

		const Vector2d operator-(const Vector2d& rhs) const {
			return Vector2d(*this) -= rhs;
		}

		const Vector2d operator*=(float scalar) {
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}

		const Vector2d operator*(float scalar) const {
			return Vector2d(*this) *= scalar;
		}

		float getLength() {
			return sqrtf((x * x) + (y * y));
		}

		void normalize() {
			float length = getLength();
			if (length > 0.0f) {
				x = x / length;
				y = y / length;
			}
			else {
				x = 0.0f;
				y = 0.0f;
			}
		}

	};

	enum ItemType {
		Item_COIN,
		Item_TREASURE,
		Item_ENEMY
	};

	struct PlayerState {
		float invTime;
		int health;
		Vector2d pos;
		bool finishedGame, won, died, invincible;
		bool movingRight, movingLeft;
		bool movingUp, movingDown;
		std::vector<ItemType> inventory;
	};

	struct ItemData {
		bool alive;
		ItemType type;
		Vector2d pos;
	};

	struct WorldState {
		int tilesPerRow;
		std::string tiles;
		Vector2d tileSize;
		Vector2d offset;
		std::vector<ItemData> items;
		bool isWalkableTile(const Vector2d& inPos, PlayerState& player);
	};

	void initializeGame(SDL_Renderer* pRenderer, PlayerState& player, WorldState& world);
	void getInput(PlayerState& player, WorldState& world);
	void updateGame(float deltaSeconds, PlayerState& player, WorldState& world);
	void renderGame(SDL_Renderer* pRenderer, const PlayerState& player,  const WorldState& world);
	void cleanup(PlayerState& player, WorldState& world);
}