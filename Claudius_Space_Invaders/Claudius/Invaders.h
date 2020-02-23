#pragma once
#include "Sprite.h"
#include "Collider.h"
#include "Transform.h"
#include "Music.h"
#include "Color.h"

struct RenderManager;


struct Invaders {


	Invaders();
	Invaders(Image& sprite_sheet, const float x, const float y, const int MAX_COUNT);
	enum class Type { A, B, C } invader_type;
	bool has_fired;

	
	// A = 11 , B-C = 22
	struct Invader
	{
		Sprite m_sprite;
		Collider m_collider;
		Color m_collider_color;
		Transform m_transform;
		Music m_move_sound;
		Music m_death_sound;
		Type invader_Type;

		static const int SIZE_X, SIZE_Y, SCALE, TIMER_LIMIT;
		bool gun_is_ready;
		bool is_hit;
		bool is_going_right;
		bool has_collided;
		int frame_count;
		int death_anim_count;
		int move_timer;
		float speed;



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
			void Update(Transform p_transform, bool& gun_is_ready, bool& has_fired);
		};
		Invader();
		Invader(Image& sprite_sheet, const float x, const float y, int p_count);
		void Initialize(Image& sprite_sheet, const float x, const float y, int p_count, Invaders::Type invader_type);
		void Render(RenderManager& renderManager);
		int Death();
		void Update(Invader* lhs_invader, Invader* rhs_invader, bool& has_fired);
		void destroy();
		void shoot();

		Invader* top_ptr;
		Invader* left_ptr;
		Invader* right_ptr;
		Invader* bottom_ptr;
		Bullet* m_bullet;

	};
	void Initialize(Invader* ptr, Image& sprite_sheet, const float x, const float y, int p_count);
	void Connect_invaders(Invader* ptr);
	void Initialize_private(Invader* ptr, Image& sprite_sheet, const float x, const float y, int p_count);
	void Update();
	void Render(RenderManager& renderManager);
	void Reset_invaders(Image& sprite_sheet);
	Invader* Traverseleft(Invader* ptr);

	int m_count;

	Invader* getleftmost();
	Invader* getrightmost();
	Invader* gettopinvader();
	Invader* getbottominvader();


	Invader* m_leftmost_invader;
	Invader* m_rightmost_invader;
	Invader* m_top_invader;
	Invader* m_bottom_invader;
	Invader* root_invader;
};