#pragma once
#include "Sprite.h"
#include "Transform.h"

struct RenderManager;

struct Interface
{
	enum class Number { Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine } m_number;
	Interface();
	Interface(Image& sprite_sheet, int lives, int score);
	Interface(Image& sprite_sheet, int score);
	struct Livesdisplay
	{
		struct Icon
		{
			Transform m_transform;
			Sprite m_sprite;
			Icon* left_ptr;
			Icon();
		};
		Icon* root_icon;
		Livesdisplay();
		Livesdisplay(Image& sprite_sheet, int lives);
		void Initialize(Image& sprite_sheet, int lives);
		void Render(RenderManager& renderManager, int lives);
		void Update(int lives);
	};
	struct Score_display
	{
		Transform m_transform;
		Sprite m_sprite;
		struct Row
		{
			Transform m_transform;
			Sprite m_sprite;
			Row* left_ptr;
			Row();
		};
		Row* root_row;
		Score_display();
		Score_display(Image& sprite_sheet, int score);
		void SetNumber(int number, int row);
		void Initialize(Image& sprite_sheet, int score);
		void Initialize_hi_score(Image& sprite_sheet, int score);
		void Render(RenderManager& renderManager);
		void Update(int score);
	};
	Score_display m_score_display;
	Livesdisplay m_lives_display;
	void Initialize(Image& sprite_sheet, int lives, int score);
	void Initialize(Image& sprite_sheet, int score);
	void Render(RenderManager& renderManager, int lives);
	void Render(RenderManager& renderManager);
	void Update(int score);
};