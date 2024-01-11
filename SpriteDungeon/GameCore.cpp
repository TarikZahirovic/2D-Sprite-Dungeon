#include "GameCore.h"
#include "Sprite.h"
#include "Hero.h"
#include "RoomRenderer.h"
#include "Item.h"
#include "HUD.h"

namespace SpriteDungeon {

	std::vector<Sprite*> SpriteList;

	//Checking whether the given tile is ok for the player to move onto
	bool WorldState::isWalkableTile(const Vector2d& inPos, PlayerState& player) {
		int col = (int)(inPos.x / tileSize.x);
		int row = (int)(inPos.y / tileSize.y);

		char current = ' ';
		int index = (row * tilesPerRow) + col;

		if (player.movingRight) {index++;}
		if (player.movingDown) {index += tilesPerRow;}

		if (index >= 0 && index < (int)tiles.size()) {
			current = tiles[index];
		}

		if (current == '.' && (player.movingRight || player.movingLeft) && !player.movingDown) {
			index += tilesPerRow;
			if (index >= 0 && index < (int)tiles.size()) {
				current = tiles[index];
			}
		}
		if (current == '.' && (player.movingDown || player.movingUp) && !player.movingRight) {
			index++;
			if (index >= 0 && index < (int)tiles.size()) {
				current = tiles[index];
			}
		}
		
		return current == '.';
	}

	//Initializing the game: populating sprite and item list vectors
	void initializeGame(SDL_Renderer* pRenderer, PlayerState& player, WorldState& world) {

		world.tileSize = Vector2d(104.0f, 104.0f);

		//World Layout
		world.tilesPerRow = 103;
		world.tiles =
			"                  _____________________________________________________________     ___________        "//1
			"                  |...|.......................................................|     |.........|        "//2
			"                  |...|.......................................................|     |.........|        "//3
			"                  |...|..|________________________________________________....|_____|.........|        "//4
			"                  |...|..|________________________________________________....................|        "//5
			"                  |...|..|..............................................||....................|        "//6
			"                  |...|..|..............................................||....................|        "//7
			"                  |...|..|...|__________..._____..._______..__________..||....|_____|.........|        "//8
			"                  |...|..|...|.........|...|||||...|||||||..||||||...|..||....|     |.........|        "//9
			"                  |...|..|...|.........|...|||||...|||||||..||||||...|..||....|     |.........|        "//10
			"                  |...|..|...|...|_____|...|||||...|||||||..||||||...|..||....|     |_________|        "//11
			"                  |...|..|...|...|.........|||||...|_____|__|____|...|..||....|                        "//12
			"                  |...|..|...|...|.........|||||.....................|..||....|                        "//13
			"                  |...|..|...|...|.........|||||.....................|..||....|                        "//14
			"                  |...|..|...|...|_________|___|_____________________|..||....|                        "//15
			"                  |...|......|..........................................||....|                        "//16
			"                  |...|......|..........................................||....|                        "//17
			"                  |...|__|...|__________________________________________||....|                        "//18
			"                  |...........................................................|                        "//19
			"                  |...........................................................|                        "//20
			"                  |...........................................................|                        "//21
			"                  |______|...|________________________________________________|                        "//22
			"                         |...|                                                                         "//23
			"                         |...|                                                                         "//24
			"                   ______|...|______        ____________                         ___________           "//25
			" ___________       |...............|        |..........|                         |.........|           "//26
			" |.........|       |...............|        |..........|                         |.........|           "//27
			" |.........|_______|...............|________|..........|_________________________|.........|           "//28
			" |.........................................................................................|           "//29
			" |.........................................................................................|           "//30
			" |.........|_______|.......................................................................|           "//31
			" |.........|       |...............|________|..........|_________________________|.........|           "//32
			" |____|..|_|       |...............|        |..........|                         |.........|           "//33
			"      |..|         |______|..|_____|        |..........|                         |.........|           "//34
			"      |..|                |..|              |__________|                         |_________|           "//35
			"      |..|                |..|                                                                         "//36
			"      |..|                |..|                                                                         "//37
			"      |..|            ____|..|_____________________________________________                            "//38
			"      |..|            |...................................................|                            "//39
			"      |..|            |...................................................|                            "//40
			"      |..|            |...................................................|                            "//41
			"      |..|            |...................................................|                            "//42
			"    __|..|___         |...................................................|                            "//43
			"    |.......|         |...................................................|                            "//44
			"    |.......|         |...................................................|                            "//45
			"    |.......|         |___________________________________________________|                            "//46
			"    |.......|                                                                                          "//47
			"    |.......|                                                                                          "//48
			"    |.......|                                                                                          "//49
			"    |_______|                                                                                          ";//50

		RoomRenderer* roomRenderer = new RoomRenderer;
		Hero* newHero = new Hero;
		Sprite* newSprite = new Sprite;
		Item* newItem = new Item;
		HUD* newHUD = new HUD;

		//Background Sprite
		newSprite = new Sprite;
		newSprite->initialize(pRenderer, "Assets/bg.bmp", 1280.0f, 720.0f);
		SpriteList.push_back(newSprite);

		//Room Renderer
		roomRenderer = new RoomRenderer;
		roomRenderer->initialize(pRenderer, "Assets/floor.bmp", "Assets/wall.bmp");
		SpriteList.push_back(roomRenderer);

		//Item Sprites
		world.items.push_back({ true, Item_COIN, Vector2d(28.0f * world.tileSize.x, 30.0f * world.tileSize.y) }); //Crossroads
		world.items.push_back({ true, Item_COIN, Vector2d(9.0f * world.tileSize.x, 47.0f * world.tileSize.y) }); //Southern Freebie
		world.items.push_back({ true, Item_COIN, Vector2d(72.0f * world.tileSize.x, 42.0f * world.tileSize.y) }); //Long Pirate Room
		world.items.push_back({ true, Item_COIN, Vector2d(92.0f * world.tileSize.x, 6.0f * world.tileSize.y) }); //End of Maze
		world.items.push_back({ true, Item_COIN, Vector2d(59.0f * world.tileSize.x, 9.0f * world.tileSize.y) }); //In-Maze

		world.items.push_back({ true, Item_TREASURE, Vector2d(90.0f * world.tileSize.x, 30.0f * world.tileSize.y) }); //Treasure

		//Enemy Sprites
		//Crossroads
		world.items.push_back({ true, Item_ENEMY, Vector2d(23.0f * world.tileSize.x, 26.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(21.0f * world.tileSize.x, 32.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(27.0f * world.tileSize.x, 31.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(35.0f * world.tileSize.x, 28.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(35.0f * world.tileSize.x, 30.0f * world.tileSize.y) });

		//Long Pirate Room
		world.items.push_back({ true, Item_ENEMY, Vector2d(24.0f * world.tileSize.x, 38.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(30.0f * world.tileSize.x, 41.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(35.0f * world.tileSize.x, 40.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(36.0f * world.tileSize.x, 41.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(42.0f * world.tileSize.x, 43.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(42.0f * world.tileSize.x, 44.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(43.0f * world.tileSize.x, 44.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(42.0f * world.tileSize.x, 42.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(47.0f * world.tileSize.x, 40.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(48.0f * world.tileSize.x, 41.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(53.0f * world.tileSize.x, 43.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(54.0f * world.tileSize.x, 43.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(55.0f * world.tileSize.x, 43.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(56.0f * world.tileSize.x, 43.0f * world.tileSize.y) });

		world.items.push_back({ true, Item_ENEMY, Vector2d(65.0f * world.tileSize.x, 43.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(65.0f * world.tileSize.x, 42.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(65.0f * world.tileSize.x, 44.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(65.0f * world.tileSize.x, 40.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(65.0f * world.tileSize.x, 38.0f * world.tileSize.y) });

		world.items.push_back({ true, Item_ENEMY, Vector2d(68.0f * world.tileSize.x, 42.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(68.0f * world.tileSize.x, 43.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(68.0f * world.tileSize.x, 44.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(68.0f * world.tileSize.x, 40.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(68.0f * world.tileSize.x, 39.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(68.0f * world.tileSize.x, 38.0f * world.tileSize.y) });

		world.items.push_back({ true, Item_ENEMY, Vector2d(70.0f * world.tileSize.x, 42.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(70.0f * world.tileSize.x, 41.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(70.0f * world.tileSize.x, 44.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(70.0f * world.tileSize.x, 40.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(70.0f * world.tileSize.x, 39.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(70.0f * world.tileSize.x, 38.0f * world.tileSize.y) });

		//Way to Treasure
		world.items.push_back({ true, Item_ENEMY, Vector2d(80.0f * world.tileSize.x, 30.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(80.0f * world.tileSize.x, 29.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(80.0f * world.tileSize.x, 28.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(81.0f * world.tileSize.x, 30.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(81.0f * world.tileSize.x, 29.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(81.0f * world.tileSize.x, 28.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(79.0f * world.tileSize.x, 30.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(79.0f * world.tileSize.x, 29.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(79.0f * world.tileSize.x, 28.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(78.0f * world.tileSize.x, 30.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(78.0f * world.tileSize.x, 29.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(78.0f * world.tileSize.x, 28.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(77.0f * world.tileSize.x, 30.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(77.0f * world.tileSize.x, 29.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(77.0f * world.tileSize.x, 28.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(76.0f * world.tileSize.x, 30.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(76.0f * world.tileSize.x, 29.0f * world.tileSize.y) });
		world.items.push_back({ true, Item_ENEMY, Vector2d(76.0f * world.tileSize.x, 28.0f * world.tileSize.y) });


		

		for (unsigned int i = 0; i < world.items.size(); i++) {
			newItem = new Item;
			switch (world.items[i].type) {
				case Item_COIN:
					newItem->initialize(pRenderer, "Assets/coin1.bmp", "Assets/coin2.bmp", 46.0f, 49.0f);
					newItem->enemy = false;
					newItem->treasure = false;
					break;
				case Item_TREASURE:
					newItem->initialize(pRenderer, "Assets/treasure.bmp", "Assets/treasure.bmp", 79.0f, 62.0f);
					newItem->enemy = false;
					newItem->treasure = true;
					break;
				case Item_ENEMY:
					newItem->initialize(pRenderer, "Assets/badPirate1.bmp", "Assets/badPirate2.bmp", 103.0f, 79.0f);
					newItem->enemy = true;
					newItem->treasure = false;
					break;
			}

			newItem->setIndex(i);
			SpriteList.push_back(newItem);
		}

		//Player Sprite
		newHero = new Hero;
		newHero->initialize(pRenderer, "Assets/pirateBoy1.bmp", "Assets/pirateBoy2.bmp", 103.0f, 79.0f);
		newHero->pos = Vector2d(5.0f * world.tileSize.x, 30.0f * world.tileSize.y);
		player.pos = newHero->pos2 + newHero->pos;
		SpriteList.push_back(newHero);

		//HUD HP Sprite
		newHUD->initialize(pRenderer, 
			"Assets/hpHUD3.bmp", 
			"Assets/hpHUD2.bmp", 
			"Assets/hpHUD1.bmp", 
			"Assets/hpHUD0.bmp", 
			"Assets/hpHUD3.bmp", 
			"Assets/hpHUD3.bmp", 
			190.0f, 75.0f);
		newHUD->hp = true;
		SpriteList.push_back(newHUD);

		//HUD Coins Sprite
		newHUD = new HUD;
		newHUD->initialize(pRenderer,
			"Assets/coins0.bmp",
			"Assets/coins1.bmp",
			"Assets/coins2.bmp",
			"Assets/coins3.bmp",
			"Assets/coins4.bmp",
			"Assets/coins5.bmp",
			161.0f, 26.0f);
		newHUD->hp = false;
		newHUD->pos = Vector2d(12.0f, 40.0f);
		SpriteList.push_back(newHUD);

		//Invincible Sprite
		newSprite = new Sprite;
		newSprite->initialize(pRenderer, "Assets/inv.bmp", 475.0f, 75.0f);
		newSprite->pos = Vector2d(340.0f, 300.0f);
		newSprite->visible = false;
		newSprite->pos = Vector2d(190.0f, 0.0f);
		SpriteList.push_back(newSprite);

		//Won Game Sprite
		newSprite = new Sprite;
		newSprite->initialize(pRenderer, "Assets/win.bmp", 713.0f, 212.0f);
		newSprite->pos = Vector2d(340.0f, 300.0f);
		newSprite->visible = false;
		SpriteList.push_back(newSprite);

		//Game Over Sprite
		newSprite = new Sprite;
		newSprite->initialize(pRenderer, "Assets/lose.bmp", 713.0f, 212.0f);
		newSprite->pos = Vector2d(340.0f, 300.0f);
		newSprite->visible = false;
		SpriteList.push_back(newSprite);

		//Setting up player state
		player.won = false;
		player.health = 3;
		player.finishedGame = false;
		player.movingRight = false;
		player.movingLeft = false;
		player.movingUp = false;
		player.movingDown = false;
	}

	//Gets input from the player, controls player movement and if player wants to quit
	void getInput(PlayerState& player, WorldState& world) {
		SDL_Event event = {};
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				player.finishedGame = true;
			}
			else if (event.type == SDL_KEYDOWN) { 
				auto keyCode = event.key.keysym.sym;
				if (keyCode == SDLK_ESCAPE) {player.finishedGame = true;}
				if (keyCode == SDLK_w || keyCode == SDLK_UP) { player.movingUp = true; }
				if (keyCode == SDLK_a || keyCode == SDLK_LEFT) { player.movingLeft = true; }
				if (keyCode == SDLK_s || keyCode == SDLK_DOWN) { player.movingDown = true; }
				if (keyCode == SDLK_d || keyCode == SDLK_RIGHT) { player.movingRight = true; }
			}
			else if (event.type == SDL_KEYUP) {
				auto keyCode = event.key.keysym.sym;
				if (keyCode == SDLK_w || keyCode == SDLK_UP) { player.movingUp = false; }
				if (keyCode == SDLK_a || keyCode == SDLK_LEFT) { player.movingLeft = false; }
				if (keyCode == SDLK_s || keyCode == SDLK_DOWN) { player.movingDown = false; }
				if (keyCode == SDLK_d || keyCode == SDLK_RIGHT) { player.movingRight = false; }
			}
		}
	}

	//Automatically updates each sprite in the game
	void updateGame(float deltaSeconds, PlayerState& player, WorldState& world) {
		for (unsigned int i = 0; i < SpriteList.size(); i++) {
			SpriteList[i]->update(deltaSeconds, player, world);
		}
		//Revealing messages
		if (player.won) {SpriteList[SpriteList.size() - 2]->visible = true;}
		if (player.died) {SpriteList[SpriteList.size() - 1]->visible = true;}
		if (player.invincible) {SpriteList[SpriteList.size() - 3]->visible = true;}
		else { SpriteList[SpriteList.size() - 3]->visible = false; }
	}

	//Renders all visible sprites
	void renderGame(SDL_Renderer* pRenderer, const PlayerState& player, const WorldState& world) {
		SDL_RenderClear(pRenderer);
		for (unsigned int i = 0; i < SpriteList.size(); i++) {
			if (i == 0 || i > SpriteList.size() - 6) {
				SpriteList[i]->render(pRenderer, player, world, Vector2d(0.0f, 0.0f));
			}
			else {
				SpriteList[i]->render(pRenderer, player, world, Vector2d(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f) - world.offset);
			}
		}
		SDL_RenderPresent(pRenderer);
	}

	//Cleanup that happens when exiting the game
	void cleanup(PlayerState& player, WorldState& world) {
		SpriteList.clear();
		Sprite::cleanupTextures();
	}
}