#pragma once
#include "Sprite.h"
#include "Collider.h"
#include "Transform.h"
#include "Music.h"
#include "Color.h"
#include "KeyCode.h"


struct Image;
struct RenderManager;

struct Player
{
	Sprite m_sprite;
	Collider m_collider;
	Color m_collider_color;
	Transform m_transform;
	Music m_firing_sound;
	Music m_death_sound;


	
	static const int SIZE_X, SIZE_Y;
	static const int SCALE;
	static float speed;
	int reload_timer;
	static bool gun_is_ready;
	bool is_hit;
	bool is_moving_left;
	bool is_moving_right;
	int death_anim_counter;
	int frame_counter;
	int lives;	

	Player();
	Player(Image& sprite_sheet, const int WIDTH, const int HEIGHT);
	void Initialize(Image& sprite_sheet, const int WIDTH, const int HEIGHT);
	void Update(const int WIDTH, const int HEIGHT);
	void Render(RenderManager& renderManager);
	void onKeydown(KeyCode key);
	void onKeyUp(KeyCode key);
	void Death();
	void resetPosition(const int WIDTH, const int HEIGHT);
	Collider& getcollider();

	struct Bullet
	{
		Sprite m_sprite;
		Transform m_transform;
		Collider m_collider;
		Color m_collider_color;

		static const int SIZE_X, SIZE_Y;
		bool has_collided;
		Bullet();
		Bullet(Image& sprite_sheet, const int WIDTH, const int HEIGHT);
		void Initialize(Image& sprite_sheet, const int WIDTH, const int HEIGHT);
		void Update(Transform p_transform);
	};
	Bullet* m_bullet;

};
