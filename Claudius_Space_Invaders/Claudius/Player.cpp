#include "Player.h"
#include "RenderManager.h"
#include "Image.h"
#include "KeyCode.h"

const int Player::SIZE_X = 26;
const int Player::SIZE_Y = 16;
const int Player::Bullet::SIZE_X = 8;
const int Player::Bullet::SIZE_Y = 16;
const int Player::SCALE = 2;
float Player::speed = 2;
bool Player::gun_is_ready = true;	


Player::Player() : is_hit(false), reload_timer(0), m_bullet(nullptr), is_moving_left(false), is_moving_right(false), death_anim_counter(0), frame_counter(0), lives(3)
{

}
Player::Player(Image& sprite_sheet, const int WIDTH, const int HEIGHT) :is_moving_left(false), is_moving_right(false), is_hit(false), death_anim_counter(0), frame_counter(0), lives(3)
{
	Initialize(sprite_sheet, WIDTH, HEIGHT);
}
void Player::Initialize(Image& sprite_sheet, const int WIDTH, const int HEIGHT) 
{
	Bullet* new_bullet = new Bullet(sprite_sheet, WIDTH, HEIGHT);
	m_bullet = new_bullet;
	m_sprite.SetImage(sprite_sheet);
	m_sprite.SetSource(277, 43, Player::SIZE_X, Player::SIZE_Y);
	m_transform.SetScale(Player::SCALE,Player::SCALE);
	m_transform.SetPosition(static_cast<float>(WIDTH) / 2.0f, static_cast<float>(HEIGHT - Player::SIZE_Y * Player::SCALE * 2.0f));
	m_collider.SetSize(Player::SIZE_X * Player::SCALE, (Player::SIZE_Y * Player::SCALE) / 2);
	m_collider_color.SetColor(0, 255, 0, 0);
	gun_is_ready = true;

}

void Player::Update(const int WIDTH, const int HEIGHT)
{
	if (is_hit == true)
	{
		m_collider.SetSize(0, 0);
		death_anim_counter++;
		if (death_anim_counter >= 120)
		{
			m_sprite.SetSource(277, 43, Player::SIZE_X, Player::SIZE_Y);
			m_collider.SetSize(Player::SIZE_X * Player::SCALE, (Player::SIZE_Y * Player::SCALE) / 2);
			m_transform.SetPosition(static_cast<float>(WIDTH) / 2.0f, static_cast<float>(HEIGHT - Player::SIZE_Y * Player::SCALE * 2.0f));
 			is_hit = false;
			is_moving_left = false;
			is_moving_right = false;
			death_anim_counter = 0;
			lives--;

		}
		else
		{
			
			if (frame_counter > 2)
			{
				m_sprite.SetSource(327, 91, 23, 14);
				frame_counter = 0;
			}
			else
			{
				m_sprite.SetSource(367, 89, 30, 17);
				frame_counter++;
			}

		}
		
		
	}
	else
	{
		if (is_moving_left)
		{
			if (m_transform.position.x - Player::speed > 0)
			{
				m_transform.ChangePosition(-Player::speed, 0);
			}
		}
		if (is_moving_right)
		{
			if (m_transform.position.x + Player::speed < 744 - Player::SIZE_X * SCALE)
			{
				m_transform.ChangePosition(Player::speed, 0);
			}
		}
		if (gun_is_ready == true)
		{
			m_bullet->m_transform.SetPosition(m_transform.GetPosition().x + Player::SIZE_X / 2.0f + 11.0f, m_transform.GetPosition().y - 24.0f);
		}
		m_collider.SetPosition(static_cast<int>(m_transform.GetPosition().x), static_cast<int>(m_transform.GetPosition().y + (Player::SIZE_Y * Player::SCALE / 2)));
		m_bullet->Update(m_transform);
	}
}

void Player::Render(RenderManager& renderManager)
{
	m_collider_color.SetColor(0, 255, 0, 0);
	renderManager.Render(m_bullet->m_collider.rect,m_collider_color);
    renderManager.Render(m_bullet->m_sprite, m_bullet->m_transform);
	renderManager.Render(m_sprite, m_transform);
	renderManager.Render(m_collider.rect, m_collider_color);
}
void Player::onKeydown(KeyCode key)
{
	switch (key)
	{
	case KeyCode::LEFT_ARROW:
		is_moving_left = true;
		break;
	case KeyCode::RIGHT_ARROW:
		is_moving_right = true;
		break;
	case KeyCode::SPACE:
		gun_is_ready = false;
		break;
	}
}
void Player::onKeyUp(KeyCode key)
{
	switch (key)
	{
	case KeyCode::LEFT_ARROW:
		is_moving_left = false;
		break;
	case KeyCode::RIGHT_ARROW:
		is_moving_right = false;
		break;
	}
}
void Player::Death()
{

}
void Player::resetPosition(const int WIDTH, const int HEIGHT)
{
}

Collider& Player::getcollider()
{
	return m_collider;
}
Player::Bullet::Bullet() : has_collided(false)
{

}
Player::Bullet::Bullet(Image& sprite_sheet, const int WIDTH, const int HEIGHT) : has_collided(false)
{
	Initialize(sprite_sheet, WIDTH, HEIGHT);
}
void Player::Bullet::Initialize(Image& sprite_sheet, const int WIDTH, const int HEIGHT)
{
	m_sprite.SetImage(sprite_sheet);
	m_sprite.SetSource(0, 0, 0, 0);
	m_transform.SetScale(Player::SCALE, Player::SCALE);
	m_transform.SetPosition(static_cast<float>(WIDTH) / 2.0f + 17.0f, static_cast<float>(HEIGHT - Player::SIZE_Y));
	m_collider.SetSize(Player::Bullet::SIZE_X * Player::SCALE, Player::Bullet::SIZE_Y * Player::SCALE);
	has_collided = false;
}
void Player::Bullet::Update(Transform p_transform)
{
	if (m_transform.GetPosition().y + 39 < 0)
	{
		has_collided = true;
	}
	if (gun_is_ready == false)
	{
		m_sprite.SetSource(415, 92, 2, 12);
		m_transform.ChangePosition(0, -7);
		m_collider.SetSize(SIZE_X * SCALE, SIZE_Y * SCALE);
	}
	if (gun_is_ready == false && has_collided == true)
	{
		m_collider.SetSize(0, 0);
		m_sprite.SetSource(0, 0, 0, 0);
		m_transform.SetPosition(p_transform.GetPosition().x + Player::SIZE_X / 2.0f + 17.0f, p_transform.GetPosition().y);
		gun_is_ready = true;
		has_collided = false;
	}
	m_collider.SetPosition(static_cast<int>(m_transform.GetPosition().x),static_cast<int>(m_transform.GetPosition().y));
}
