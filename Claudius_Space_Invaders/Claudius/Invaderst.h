#pragma once
#include "Sprite.h"
#include "Collider.h"
#include "Transform.h"
#include "Music.h"
#include "Color.h"

struct RenderManager;

struct Invader
{
	Sprite m_sprite;
	Collider m_collider;
	Color m_collider_color;
	Transform m_transform;
	Music m_move_sound;
	Music m_death_sound;

	static const int SIZE_X, SIZE_Y, SCALE;
	static bool gun_is_ready;
	bool is_hit;

	

	struct Bullet
	{
		Sprite m_sprite;
		Transform m_transform;
		Collider m_collider;
		Color m_collider_color;
		
		static const int SIZE_X, SIZE_Y;
		bool has_collided;

		Bullet();
		Bullet(Image& sprite_sheet, int x, int y);

		void Initialize(Image& sprite_sheet, int x, int y);
		void Update(Transform p_transform);
	};
	Invader();
	Invader(Image& sprite_sheet, const float x, const float y);
	void Initialize(Image& sprite_sheet, const float x, const float y);
	void Render(RenderManager& renderManager);
	void Death();
	void Update(const int WIDTH, const int HEIGHT);
	void destroy();
	void shoot();
	void resetPosition(const int WIDTH, const int HEIGHT);
	
	Bullet* m_bullet;

};