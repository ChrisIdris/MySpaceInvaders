#include "Invaders.h"
#include "RenderManager.h"
#include "Image.h"
#include "KeyCode.h"

const int Invaders::Invader::Bullet::SIZE_X = 6; // 413
const int Invaders::Invader::Bullet::SIZE_Y = 12; // 92
const int Invaders::Invader::SIZE_X = 16;
const int Invaders::Invader::SIZE_Y = 17;
const int Invaders::Invader::SCALE = 2;
//bool Invaders::Invader::gun_is_ready = true;
//bool Invaders::Invader::is_hit = false;
//bool Invaders::Invader::is_going_right = true;
//int Invaders::Invader::frame_count = 0;
// Bullet
Invaders::Invader::Bullet::Bullet() : has_collided(false)
{

}
Invaders::Invader::Bullet::Bullet(Image& sprite_sheet, int x, int y) : has_collided(false)
{
	Initialize(sprite_sheet, x, y);

}
void Invaders::Invader::Bullet::Initialize(Image& sprite_sheet, int x, int y)
{
	m_sprite.SetImage(sprite_sheet);
	m_sprite.SetSource(0, 0,0,0);
	m_transform.SetScale(static_cast<float>(Invader::SCALE), static_cast<float>(Invader::SCALE));
	m_transform.SetPosition(static_cast<const float>(x), static_cast<const float>(y));
	m_collider.SetSize(0, 0);

}
void Invaders::Invader::Bullet::Update(Transform p_transform, bool& gun_is_ready, bool& has_fired)
{

	if (m_transform.GetPosition().y > 840 + SIZE_X * SCALE)
	{
		has_collided = true;
		m_collider.SetSize(0, 0);
	}
	if (gun_is_ready == false)
	{
		m_sprite.SetSource(413, 92, SIZE_X, SIZE_Y);
		m_transform.ChangePosition(0, 4);
		m_transform.ChangeRotation(180.0f);
		m_collider.SetSize(SIZE_X * SCALE, SIZE_Y * SCALE);
		has_fired = true;

	}
	if (gun_is_ready == false && has_collided == true)
	{
		m_sprite.SetSource(0, 0, 0, 0);
		m_transform.SetPosition(p_transform.GetPosition().x + Invader::SIZE_X * SCALE / 2, p_transform.GetPosition().y);
		gun_is_ready = true;
		has_fired = false;
		has_collided = false;
	}
	m_collider.SetPosition(static_cast<int>(m_transform.GetPosition().x), static_cast<int>(m_transform.GetPosition().y));

}
// Invader
Invaders::Invader::Invader() : m_bullet(nullptr) , invader_Type(Type::A), move_timer(0), is_going_right(true),gun_is_ready(true), frame_count(0), speed(3), death_anim_count(0), is_hit(false)
{
	this->has_collided = false;
	top_ptr = nullptr;
	bottom_ptr = nullptr;
	left_ptr = nullptr;
	right_ptr = nullptr;
}
Invaders::Invader::Invader(Image& sprite_sheet, const float x, const float y, int p_count) : m_bullet(nullptr), gun_is_ready(true), is_going_right(true), frame_count(0),move_timer(0), speed(3), death_anim_count(0), is_hit(false)
{
	this->has_collided = false;
	top_ptr = nullptr;
	bottom_ptr = nullptr;
	left_ptr = nullptr;
	right_ptr = nullptr;
	Type temp_type;
	if (p_count > 11)
	{
		if (p_count > 33)
		{
			temp_type = Type::C;
		}
		else
		{
			temp_type = Type::B;
		}
	}
	else
	{
		temp_type = Type::A;
	}
	Initialize(sprite_sheet, x, y, p_count, temp_type);
}
void Invaders::Invader::Initialize(Image& sprite_sheet, const float x, const float y, int p_count, Type invader_type)
{
	float position_x, position_y;
	int distance = 60;
	switch (invader_type)
	{
	case Type::A:
		m_sprite.SetImage(sprite_sheet);
		m_sprite.SetSource(7, 40, SIZE_X, SIZE_Y);
		invader_Type = Type::A;
		break;
	case Type::B:
		m_sprite.SetImage(sprite_sheet);
		m_sprite.SetSource(74, 40, 22, 17);
		invader_Type = Type::B;
		break;
	case Type::C:
		m_sprite.SetImage(sprite_sheet);
		m_sprite.SetSource(147, 41, 24, 17);
		invader_Type = Type::C;
		break;
	}
	position_x = static_cast<float>(p_count * distance) + 5;
	int temp = 11;
	if (p_count > 11)
	{
		position_x = static_cast<float>((p_count - temp) * distance);
		if (p_count > 22)
		{
			position_x = static_cast<float>((p_count - temp * 2) * distance);
			if (p_count > 33)
			{
				position_x = static_cast<float>((p_count - temp * 3) * distance);
				if (p_count > 44)
				{
					position_x = static_cast<float>((p_count - temp * 4.0f) * distance);
					position_y = static_cast<float>(y * 5.0f + distance * 4.0f);
					m_transform.SetPosition(position_x, position_y);
					m_collider.SetSize(SIZE_X * SCALE + 20, SIZE_Y * SCALE);
				}
				else
				{
					position_y = static_cast<float>(y * 4.0f + distance * 3.0f);
					m_transform.SetPosition(position_x, position_y);
					m_collider.SetSize(SIZE_X * SCALE + 20, SIZE_Y * SCALE);
				}
			}
			else
			{
				position_y = static_cast<float>(y * 3.0f + distance * 2.0f);
				m_transform.SetPosition(position_x, position_y);
				m_collider.SetSize(SIZE_X * SCALE + 10, SIZE_Y * SCALE);
			}
		}
		else
		{
			position_y = static_cast<float>(y * 2.0f + distance);
			m_transform.SetPosition(position_x, position_y);
			m_collider.SetSize(SIZE_X * SCALE + 10, SIZE_Y * SCALE);
		}
	}
	else
	{
		m_transform.SetPosition(position_x, y);
		m_collider.SetSize(SIZE_X * SCALE, SIZE_Y * SCALE);

	}
	m_transform.SetScale(static_cast<float>(SCALE), static_cast<float>(SCALE));
	m_bullet = new Bullet(sprite_sheet, static_cast<int>(x), static_cast<int>(y));

}
void Invaders::Invader::Render(RenderManager& renderManager)
{

	if (death_anim_count < 60)
	{
		m_collider_color.SetColor(0, 255, 0, 0);
		renderManager.Render(m_bullet->m_sprite, m_bullet->m_transform);
		renderManager.Render(m_sprite, m_transform);
		renderManager.Render(m_collider.rect, m_collider_color);
	}

}
void Invaders::Invader::Update(Invader* lhs_invader, Invader* rhs_invader, bool& has_fired)
{
	if (is_hit == true)
	{
		if (death_anim_count < 60)
		{
			if (frame_count > 2)
			{
				m_sprite.SetSource(437, 90, 26, 17);
				frame_count = 0;
			}
			else
			{
				m_sprite.SetSource(437, 90, 26, 17);
				m_sprite.SetSource(0, 0, 0, 0);
				frame_count++;
			}
			death_anim_count++;
		}
		else
		{
			m_sprite.SetSource(437, 90, 26, 17);
		    m_sprite.SetSource(0, 0, 0, 0);
		}
	}
	if (is_hit != true)
	{
		if (move_timer > 10 )
		{
			if (is_going_right == true)
			{
				m_transform.ChangePosition(speed, 0);
				if (frame_count == 0)
				{
					switch (invader_Type)
					{
					case Type::A:
						m_sprite.SetSource(7, 40, SIZE_X, SIZE_Y);
						break;
					case Type::B:
						m_sprite.SetSource(107, 40, 22, 17);
						break;
					case Type::C:
						m_sprite.SetSource(179, 41, 24, 17);
						break;
					}
					frame_count++;
				}
				else
				{
					switch (invader_Type)
					{
					case Type::A:
						m_sprite.SetSource(40, 40, SIZE_X, SIZE_Y);
						break;
					case Type::B:
						m_sprite.SetSource(74, 40, 22, 17);
						break;
					case Type::C:
						m_sprite.SetSource(147, 41, 24, 17);
						break;
					}
					frame_count = 0;
				}

			}
			if (is_going_right == false)
			{
				m_transform.ChangePosition(-speed, 0);
				if (frame_count == 0)
				{
					switch (invader_Type)
					{
					case Type::A:
						m_sprite.SetSource(7, 40, SIZE_X, SIZE_Y);
						break;
					case Type::B:
						m_sprite.SetSource(107, 40, 22, 17);
						break;
					case Type::C:
						m_sprite.SetSource(179, 41, 24, 17);
						break;
					}
					frame_count++;
				}
				else
				{
					switch (invader_Type)
					{
					case Type::A:
						m_sprite.SetSource(40, 40, SIZE_X, SIZE_Y);
						break;
					case Type::B:
						m_sprite.SetSource(74, 40, 22, 17);
						break;
					case Type::C:
						m_sprite.SetSource(147, 41, 24, 17);
						break;
					}
					frame_count = 0;
				}

			}
			move_timer = 0;
		}
		move_timer++;
	}
	if (gun_is_ready == true)
	{
		m_bullet->m_transform.SetPosition(m_transform.GetPosition().x + SIZE_X * SCALE / 2, m_transform.GetPosition().y);
	}
	m_collider.SetPosition(static_cast<int>(m_transform.GetPosition().x), static_cast<int>(m_transform.GetPosition().y));
	m_bullet->Update(m_transform, gun_is_ready, has_fired);
}
int Invaders::Invader::Death()
{
	is_hit = true;
	m_collider.SetSize(0, 0);
	int points = 0;
	switch (invader_Type)
	{
	case Type::A:
		points += 30;
		break;
	case Type::B:
		points += 20;
		break;
	case Type::C:
		points += 30;
		break;
	}
	return points;

}

// Invaders
Invaders::Invaders() : invader_type(Type::A), m_count(0), has_fired(false)
{
	m_top_invader = nullptr;
	m_bottom_invader = nullptr;
	m_leftmost_invader = nullptr;
	m_rightmost_invader = nullptr;
	root_invader = nullptr;
}
Invaders::Invaders(Image& sprite_sheet, const float x, const float y, const int MAX_COUNT) : invader_type(Type::A), m_count(0), has_fired(false)
{
	m_top_invader = nullptr;
	m_bottom_invader = nullptr;
	m_leftmost_invader = nullptr;
	m_rightmost_invader = nullptr;
	root_invader = nullptr;
	for (int i = 0; i < MAX_COUNT; i++)
	{
			Initialize(root_invader, sprite_sheet, x, y, i + 1);
	}
	Connect_invaders(root_invader);

}

void Invaders::Initialize(Invader* ptr, Image& sprite_sheet, const float x, const float y, int p_count)
{
	if (root_invader == nullptr)
	{
		Invader* new_invader = new Invader(sprite_sheet, x, y, p_count);
		m_top_invader = new_invader;
		m_bottom_invader = new_invader;
		m_leftmost_invader = new_invader;
		root_invader = new_invader;
		m_count++;
	}
	else
	{
		Invader* temp;
		temp = ptr;
		if (p_count > 11)
		{
			if (p_count > 22)
			{
				if (p_count > 33)
				{
					if (p_count > 44)
					{
						if (root_invader->bottom_ptr->bottom_ptr->bottom_ptr->bottom_ptr == nullptr)
						{
							Invader* new_invader = new Invader(sprite_sheet, x, y, p_count);
							root_invader->bottom_ptr->bottom_ptr->bottom_ptr->bottom_ptr = new_invader;
							m_bottom_invader = new_invader;
							m_count++;
						}
						else
						{
							temp = temp->bottom_ptr->bottom_ptr->bottom_ptr->bottom_ptr;
							Initialize_private(temp, sprite_sheet, x, y, p_count);
						}
					}
					else
					{
						if (root_invader->bottom_ptr->bottom_ptr->bottom_ptr == nullptr)
						{
							Invader* new_invader = new Invader(sprite_sheet, x, y, p_count);
							root_invader->bottom_ptr->bottom_ptr->bottom_ptr = new_invader;
							m_bottom_invader = new_invader;
							m_count++;
						}
						else
						{
							temp = temp->bottom_ptr->bottom_ptr->bottom_ptr;
							Initialize_private(temp, sprite_sheet, x, y, p_count);

						}
					}
				}
				else
				{
					if (root_invader->bottom_ptr->bottom_ptr == nullptr)
					{
						Invader* new_invader = new Invader(sprite_sheet, x, y, p_count);
						root_invader->bottom_ptr->bottom_ptr = new_invader;
						m_bottom_invader = new_invader;
						m_count++;
					}
					else
					{
						temp = temp->bottom_ptr->bottom_ptr;
						Initialize_private(temp, sprite_sheet, x, y, p_count);

					}
				}
			}
			else
			{
				if (root_invader->bottom_ptr == nullptr)
				{
					Invader* new_invader = new Invader(sprite_sheet, x, y, p_count);
					root_invader->bottom_ptr = new_invader;
					m_bottom_invader = new_invader;
					m_count++;
				}
				else
				{
					temp = temp->bottom_ptr;
					Initialize_private(temp, sprite_sheet,x,y,p_count);

					/*if (temp->right_ptr != nullptr)
					{
						Initialize(temp->right_ptr, sprite_sheet, x, y, p_count);
					}
					else
					{
						Invader* new_invader = new Invader(sprite_sheet, x, y, p_count);
						temp->right_ptr = new_invader;
						temp->right_ptr->left_ptr = ptr;
						m_count++;
					}*/

				}
			}


		}
		else
		{
		     Initialize_private(temp, sprite_sheet, x, y, p_count);
		}
	}
	

	

}
void Invaders::Connect_invaders(Invader* ptr)
{
	Invader* temp_1;
	Invader* temp_2;
	temp_1 = root_invader;
	temp_2 = temp_1->bottom_ptr;
	for (int i = 0; i < 11; i++)
	{
		if (temp_1 != nullptr && temp_2 != nullptr)
		{
			temp_2->top_ptr = temp_1;
			temp_1->bottom_ptr = temp_2;
			temp_1 = temp_1->right_ptr;
			temp_2 = temp_2->right_ptr;
		}
	}
	temp_1 = root_invader->bottom_ptr;
	temp_2 = temp_1->bottom_ptr;
	for (int i = 0; i < 11; i++)
	{
		if (temp_1 != nullptr)
		{
			temp_2->top_ptr = temp_1;
			temp_1->bottom_ptr = temp_2;
			temp_1 = temp_1->right_ptr;
			temp_2 = temp_2->right_ptr;
		}
	}
	temp_1 = root_invader->bottom_ptr->bottom_ptr;
	temp_2 = temp_1->bottom_ptr;
	for (int i = 0; i < 11; i++)
	{
		if (temp_1 != nullptr)
		{
			temp_2->top_ptr = temp_1;
			temp_1->bottom_ptr = temp_2;
			temp_1 = temp_1->right_ptr;
			temp_2 = temp_2->right_ptr;
		}
	}
	temp_1 = root_invader->bottom_ptr->bottom_ptr->bottom_ptr;
	temp_2 = temp_1->bottom_ptr;
	for (int i = 0; i < 11; i++)
	{
		if (temp_1 != nullptr)
		{
			temp_2->top_ptr = temp_1;
			temp_1->bottom_ptr = temp_2;
			temp_1 = temp_1->right_ptr;
			temp_2 = temp_2->right_ptr;
		}
	}
	temp_1 = root_invader->bottom_ptr->bottom_ptr->bottom_ptr;
	temp_2 = temp_1->bottom_ptr;
	for (int i = 0; i < 11; i++)
	{
		if (temp_1 != nullptr)
		{
			temp_2->top_ptr = temp_1;
			temp_1->bottom_ptr = temp_2;
			temp_1 = temp_1->right_ptr;
			temp_2 = temp_2->right_ptr;
		}
	}

}
void Invaders::Initialize_private(Invader* ptr, Image& sprite_sheet, const float x, const float y, int p_count)
{
		if (ptr->right_ptr != nullptr)
		{
			Initialize_private(ptr->right_ptr, sprite_sheet, x, y, p_count);
		}
		else
		{
			
			Invader* new_invader = new Invader(sprite_sheet, x, y, p_count);
			ptr->right_ptr = new_invader;
			ptr->right_ptr->left_ptr = ptr;
			m_count++;
			if (p_count == 11)
			{
				m_rightmost_invader = new_invader;
			}
		}
	
}
void Invaders::Update()
{
	int move_counter = 0;
	getleftmost();
	getrightmost();
	Invader* temp;
	Invader* temp_2;
	temp = root_invader;

		if (m_leftmost_invader->m_transform.GetPosition().x - m_leftmost_invader->speed < 0 || m_rightmost_invader->m_transform.GetPosition().x + m_rightmost_invader->speed > 744 - 32)
		{
			Invader* temp_3;
			Invader* temp_4;
			temp_3 = root_invader;

			for (int x = 0; x < 11; x++)
			{
				temp_4 = temp_3;
				for (int z = 0; z < 5; z++)
				{
					if (temp_4->is_going_right == true)
					{
						temp_4->m_transform.ChangePosition(-temp_4->speed, 16);
						temp_4->is_going_right = false;
						temp_4 = temp_4->bottom_ptr;
					}
					else
					{
						temp_4->m_transform.ChangePosition(temp_4->speed, 16);
						temp_4->is_going_right = true;
						temp_4 = temp_4->bottom_ptr;
					}
				}
				temp_3 = temp_3->right_ptr;

			}
		}
		else
		{
			for (int i = 0; i < 11; i++)
			{

				temp_2 = temp;
				for (int y = 0; y < 5; y++)
				{
					if (has_fired == false)
					{
						if (temp_2->is_hit != true)
						{
							temp_2->gun_is_ready = false;
						}
					}
					temp_2->Update(m_leftmost_invader, m_rightmost_invader, has_fired);
					temp_2 = temp_2->bottom_ptr;

				}
				temp = temp->right_ptr;
			}

		}


		
	
}
void Invaders::Render(RenderManager& renderManager)
{
	Invader* temp;
	Invader* temp_2;
	temp = root_invader;
	temp_2 = temp;
	for (int i = 0; i < 11; i++)
	{
		for (int y = 0; y < 5; y++)
		{
			if (temp_2->bottom_ptr != nullptr)
			{
				temp_2->Render(renderManager);
				temp_2 = temp_2->bottom_ptr;
			}
		}
		temp_2->Render(renderManager);
		temp = temp->right_ptr;
		temp_2 = temp;
	}

}
void Invaders::Reset_invaders(Image& sprite_sheet)
{
	Invader* temp = root_invader;
	Invader* temp_2;
	int temp_count = 1;
	for(int i = 0; i < 11; i++)
	{ 
		temp_2 = temp;
		for (int i = 0; i < 5; i++)
		{
			temp->Initialize(sprite_sheet, 5, 5, temp_count, temp->invader_Type);
			temp_count++;
			temp->bottom_ptr;
		}
		temp = temp->right_ptr;
	}
}
Invaders::Invader* Invaders::Traverseleft(Invader* ptr)
{
	if (ptr->is_hit != true)
	{
		return ptr;
	}
	else
	{
		if (ptr->left_ptr != nullptr)
		{
			return Traverseleft(ptr->left_ptr);
		}
		else
		{
			return ptr;
		}

	}
}
Invaders::Invader* Invaders::getleftmost()
{
	if (m_leftmost_invader->is_hit != true)
	{
		return m_leftmost_invader;
	}
	else
	{
		Invader* temp;
		Invader* temp_2;
		temp = m_leftmost_invader;
		for (int y = 0; y < 11; y++)
		{
			temp_2 = temp;
			for (int i = 0; i < 5; i++)
			{
				if (temp_2->is_hit != true)
				{
					m_leftmost_invader = temp;
					return m_leftmost_invader;
				}
				else
				{
					temp_2 = temp_2->bottom_ptr;
				}

			}
			temp = temp->right_ptr;
		}
	}
	return m_leftmost_invader;
}
Invaders::Invader* Invaders::getrightmost()
{
	if (m_rightmost_invader->is_hit != true)
	{
		return m_rightmost_invader;
	}
	else
	{
		Invader* temp;
		Invader* temp_2;
		temp = m_rightmost_invader;
		for (int y = 0; y < 11; y++)
		{
			
			temp_2 = temp;
			for (int i = 0; i < 5; i++)
			{
				if (temp_2->is_hit != true)
				{
					m_rightmost_invader = temp;
					return m_rightmost_invader;
				}
				else
				{
					temp_2 = temp_2->bottom_ptr;
				}
				
			}
			temp = temp->left_ptr;
		}
	}
	return m_rightmost_invader;

	/*if (m_leftmost_invader->is_hit != true)
	{
		return m_leftmost_invader;
	}
	else
	{
		Invader* temp;
		if (ptr->is_hit != true)
		{
			temp = ptr;
			if (root_invader->bottom_ptr->is_hit != true)
			{
				m_leftmost_invader = root_invader->bottom_ptr;
				return m_leftmost_invader;
			}

		}
		else
		{
			getleftmost(ptr->right_ptr);
		}
		
	}*/
}

Invaders::Invader* Invaders::gettopinvader()
{
	if (m_top_invader->is_hit != true)
	{
		return m_top_invader;
	}
	else
	{
		Invader* temp;
		Invader* temp_2;
		temp = m_top_invader;
		for (int y = 0; y < 5; y++)
		{

			temp_2 = temp;
			for (int i = 0; i < 11; i++)
			{
				if (temp_2->is_hit != true)
				{
					m_rightmost_invader = temp;
					return m_rightmost_invader;
				}
				else
				{
					temp_2 = temp_2->right_ptr;
				}

			}
			temp = temp->bottom_ptr;

		}
		{

		}
	}
	return m_top_invader;
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