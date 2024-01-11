#include "RoomRenderer.h"

using namespace SpriteDungeon;

//Initializes the wall/floor sprite
void RoomRenderer::initialize(SDL_Renderer* pRenderer, const std::string& filePath1, const std::string& filePath2) {
	floor = loadTexture(pRenderer, filePath1);
	wall = loadTexture(pRenderer, filePath2);
	texture = floor;
}

//Rendering the room sprite based on the string representation of the world
void RoomRenderer::render(SDL_Renderer* pRenderer, const PlayerState& player, const WorldState& world, const Vector2d& baseTrans) {
	int colsRendered = 0, rowsRendered = 0;
	for (unsigned int i = 0; i < world.tiles.size(); i++) {
		char current = world.tiles[i];
		switch (current) {
			case '_' :
			case '|' :
				texture = wall;
				break;
			case '.' :
				texture = floor;
				break;
			default:
				texture = nullptr;
		}
		if (texture != nullptr) {
			//Camera tracking
			SDL_Rect destRect = { 
				colsRendered * (int)world.tileSize.x + (int)baseTrans.x, 
				rowsRendered * (int)world.tileSize.y + (int)baseTrans.y, 
				(int)world.tileSize.x, 
				(int)world.tileSize.y 
			};
			SDL_RenderCopy(pRenderer, texture, nullptr, &destRect);
		}
		colsRendered++;
		if (colsRendered % world.tilesPerRow == 0) {
			rowsRendered++;
			colsRendered = 0;
		}
	}
}