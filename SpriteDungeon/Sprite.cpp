#include "Sprite.h"

using namespace SpriteDungeon;

std::vector<Sprite::LoadedTexture> Sprite::s_LoadedTextures;

//Constructor
Sprite::Sprite() :
	texture(nullptr),
	pos(0.0f, 0.0f),
	pos2(104.0f, 104.0f),
	size(104.0f, 104.0f),
	visible(true)
{}

//Loads texture for this sprite and sets the size to the specified parameters
void Sprite::initialize(SDL_Renderer* pRenderer, const std::string& filePath, float width, float height) {
	texture = loadTexture(pRenderer, filePath);
	size.x = width;
	size.y = height;
}

//Updates sprite 
void Sprite::update(float deltaSeconds, PlayerState& player, WorldState& world) {}

//Renders the sprite to the screen
void Sprite::render(SDL_Renderer* pRenderer, const PlayerState& player, const WorldState& world, const Vector2d& baseTrans) {
	SDL_Rect destRect = { 
		(int)pos.x + (int)baseTrans.x, 
		(int)pos.y + (int)baseTrans.y, 
		(int)size.x, (int)size.y 
	};
	if (texture != nullptr && visible) {
		SDL_RenderCopy(pRenderer, texture, nullptr, &destRect);
	}
}

//Deletes the SDL Texture for this sprite
void Sprite::cleanup() {
	SDL_DestroyTexture(texture);
}

//Deletes the entire vector of loaded textures
void Sprite::cleanupTextures() {
	for (unsigned int i = 0; i < s_LoadedTextures.size(); i++) {
		SDL_DestroyTexture(s_LoadedTextures[i].textureCheck);
	}
	s_LoadedTextures.clear();
}

//Loads textures from a given file path, making sure to not copy files if it has already been loaded
SDL_Texture* Sprite::loadTexture(SDL_Renderer* pRenderer, const std::string& filePath) {

	for (unsigned int i = 0; i < s_LoadedTextures.size(); i++) {
		if (s_LoadedTextures[i].filename == filePath) {
			return s_LoadedTextures[i].textureCheck;
		}
	}

	SDL_Surface* pBmp = SDL_LoadBMP(filePath.c_str());
	SDL_SetColorKey(pBmp, SDL_TRUE, SDL_MapRGB(pBmp->format, 0, 255, 0));
	SDL_Texture* retTexture = SDL_CreateTextureFromSurface(pRenderer, pBmp);
	SDL_FreeSurface(pBmp);

	LoadedTexture loadedTexture = { filePath, retTexture };
	s_LoadedTextures.push_back(loadedTexture);

	return retTexture;
}