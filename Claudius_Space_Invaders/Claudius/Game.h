#pragma once

#include <string>
#include <vector>
#include "KeyCode.h"

#include "Font.h"
#include "Text.h"
#include "Sound.h"
#include "Music.h"
#include "Image.h"
#include "Player.h"
#include "Sprite.h"
#include "Image.h"
#include "Invaders.h"
#include "Interface.h"


struct RenderManager;
struct ResourceManager;
struct SoundManager;

class Game
{
	Sound sound;
	int m_score;
	int m_hi_score;
	int m_lives;

	Font font;
	Text text[4];
	int soundVolume = 100;
	Music music;
	int musicVolume = 100;
	Image image[2];
	Player player;
	Image sprite_sheet, background;
	Invaders invaders;
	Interface interface;
	Interface hi_score;


	static const int WIDTH, HEIGHT, SCALE;


	ResourceManager& resourceManager;
	SoundManager& soundManager;
public:
	
	// references to a resource and sound manager sent in the constructor
	Game(ResourceManager& resourceManager, SoundManager& soundManager);
	~Game();

	// References sent to the game from the base to set the window size and name
	bool Enter(int& width, int& height, std::string& title); 

	// If Games update returns false the program will exit, dt is milliseconds passed since last frame
	bool Update(float dt);

	// reference to the rendermanager sent in the function call, make sure to separate update logic from render logic
	void Render(RenderManager& rendererManager);
	void OnKeyDown(KeyCode key);
	void OnKeyUp(KeyCode key);
};