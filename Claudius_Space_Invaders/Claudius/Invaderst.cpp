#include "Invader.h"
#include "RenderManager.h"
#include "Image.h"
#include "KeyCode.h"

const int Invader::Bullet::SIZE_X = 6; // 413
const int Invader::Bullet::SIZE_Y = 12; // 92
const int Invader::SIZE_X = 16; // 7
const int Invader::SIZE_Y = 17; // 40
const int Invader::SCALE = 2;
bool Invader::gun_is_ready = true;
Invader::Bullet::Bullet() : has_collided(false)
{

}
Invader::Bullet::Bullet(Image& sprite_sheet, int x, int y) : has_collided(false)
{
	Initialize(sprite_sheet, x, y);

}
void Invader::Bullet::Initialize(Image& sprite_sheet, int x, int y)
{
	m_sprite.SetImage(sprite_sheet);
	m_sprite.SetSource(7, 40, Invader::Bullet::SIZE_X * Invader::SCALE, Invader::Bullet::SIZE_Y * Invader::SCALE);
	m_transform.SetScale(static_cast<float>(Invader::SCALE), static_cast<float>(Invader::SCALE));
	m_transform.SetPosition(static_cast<const float>(x), static_cast<const float>(y));

}
void Invader::Bullet::Update(Transform p_transform)
{
	if (m_transform.GetPosition().y > 768 + SIZE_X * SCALE)
	{
		has_collided = true;
	}
	if (gun_is_ready == false)
	{
		m_sprite.SetSource(413, 92, SIZE_X, SIZE_Y);
		m_transform.ChangePosition(0, 4);
		m_transform.ChangeRotation(180.0f);

	}
	if (gun_is_ready == false && has_collided == true)
	{
		m_sprite.SetSource(0, 0, 0, 0);
		m_transform.SetPosition(p_transform.GetPosition().x + Invader::SIZE_X * SCALE / 2, p_transform.GetPosition().y);
	}
	m_collider.SetPosition(static_cast<int>(m_transform.GetPosition().x), static_cast<int>(m_transform.GetPosition().y));

}
Invader::Invader() : m_bullet(nullptr), is_hit(false)
{

}
Invader::Invader(Image& sprite_sheet, const float x, const float y) : m_bullet(nullptr), is_hit(false)
{
	Initialize(sprite_sheet, x, y);
}
void Invader::Initialize(Image& sprite_sheet, const float x, const float y)
{
	m_sprite.SetImage(sprite_sheet);
	m_sprite.SetSource(7, 40, SIZE_X, SIZE_Y);
	m_transform.SetScale(SCALE, SCALE);
	m_transform.SetPosition(x, y);
	m_collider.SetSize(SIZE_X * SCALE, SIZE_Y * SCALE);

}
void Invader::Render(RenderManager& renderManager)
{

	renderManager.Render(m_sprite, m_transform);
	renderManager.Render(m_bullet->m_sprite, m_bullet->m_transform);
	renderManager.Render(m_collider.rect, m_collider_color);

}
void Invader::Update(const int WIDTH, const int HEIGHT)
{
	if (is_hit == true)
	{
		Death();
		resetPosition(WIDTH, HEIGHT);
	}
	if()
}
/*
 bool intersect(const Vector2 &point, const AxisAlignedBoundingBox & aligned_box)
 {
   auto pointToCircle = circle.center_ - point;

   return pointToCircle.length_squared() <= circle.radius_ * circle.radius_;
        or

     float x = circle.center_.x_ = point.x_;
	 float y = circle.center_.y_ = point.y_;
	 float length = (float)sqrt((double) x * x + y * y));

	 return lengthSqr <= circle.radius_ * circle.radius_;
 }
 */