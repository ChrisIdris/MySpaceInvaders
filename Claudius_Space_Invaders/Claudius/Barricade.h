#pragma once
#include "Transform.h"
#include "Color.h"
#include "Collider.h"
#include "Sprite.h"

struct RenderManager;
class Barricade
{
	Transform m_transform;
	Collider m_collider;
	Sprite m_sprite;
	Color m_collider_color;

	Barricade(Image& sprite_sheet);
	void Initialize(Image& sprite_sheet);
	void Render(RenderManager& renderManager);
	void Update();


};

