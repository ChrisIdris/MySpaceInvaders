#include "Game.h"
#include <assert.h>
#include "ResourceManager.h"
#include "RenderManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"

const int Game::SCALE = 3, Game::WIDTH = Game::SCALE * 248, Game::HEIGHT = Game::SCALE * 280;

Game::Game(ResourceManager& resourceManager, SoundManager& soundManager) : resourceManager(resourceManager), soundManager(soundManager), m_lives(3), m_score(0), m_hi_score(0)
{
	resourceManager.LoadImageFromFile(sprite_sheet, "../Assets/sprite_sheet3.png");
	player = { sprite_sheet, Game::WIDTH, Game::HEIGHT };
	invaders = { sprite_sheet, 5,5, 55 };
	interface = { sprite_sheet, m_lives, m_score };
	hi_score = { sprite_sheet, m_score };
	resourceManager.LoadSoundFromFile(sound, "../Assets/test.ogg");
	soundManager.PlaySound(sound, 1);
}

Game::~Game()
{                                                                            
}

bool Game::Enter(int& width, int& height, std::string& title)
{
	width = 744;
	height = 840;
	title = "Space_Invaders";
	return true;
}


bool Game::Update(float dt)
{	
	Invaders::Invader* temp = invaders.root_invader;
	Invaders::Invader* temp_2;
	player.Update(Game::WIDTH, Game::HEIGHT);
	if (player.is_hit != true)
	{
		invaders.Update();
		for (int x= 0; x < 11; x++)
		{
			temp_2 = temp;
			for (int y = 0; y < 5; y++)
			{
					if (CollisionManager::CheckCollision(player.m_bullet->m_collider, temp_2->m_collider) && !temp_2->is_hit)
					{
						player.m_bullet->has_collided = true;
						m_score += temp_2->Death();
					}
				temp_2 = temp_2->bottom_ptr;
			}
			temp = temp->right_ptr;
		}
	}
	// Bullet -> Player
	temp = invaders.root_invader;
	for (int z = 0; z < 11; z++)
	{
		temp_2 = temp;
		for (int a = 0; a < 5; a++)
		{
			if (CollisionManager::CheckCollision(player.m_collider, temp_2->m_bullet->m_collider))
			{
				temp_2->m_bullet->has_collided = true;
				player.is_hit = true;
			}
			temp_2 = temp_2->bottom_ptr;
		}
		temp = temp->right_ptr;

	} 
	m_lives = player.lives;
	interface.Update(m_score);
	if (m_lives == 0)
	{
		if (m_score > m_hi_score)
		{
			hi_score.Update(m_score);
			m_hi_score = m_score;
		}
		player.lives = 3;
		m_score = 0;
		//invaders.Reset_invaders(sprite_sheet);

	}


	
	return true;
}

void Game::Render(RenderManager& renderManager)
{
	invaders.Render(renderManager);
	player.Render(renderManager);
	interface.Render(renderManager, m_lives);
	hi_score.Render(renderManager);
}

void Game::OnKeyDown(KeyCode key)
{
	player.onKeydown(key);
}
void Game::OnKeyUp(KeyCode key)
{
	player.onKeyUp(key);
}
