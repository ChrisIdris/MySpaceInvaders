#include "Interface.h"
#include "RenderManager.h"
Interface::Livesdisplay::Livesdisplay() : root_icon(nullptr)
{
}
Interface::Livesdisplay::Livesdisplay(Image& sprite_sheet, int lives): root_icon(nullptr)
{
	Initialize(sprite_sheet, lives);
}
void Interface::Livesdisplay::Initialize(Image& sprite_sheet, int lives)
{	
	if (root_icon == nullptr)
	{
		float distance = 40;
		root_icon = new Icon();
		root_icon->m_sprite.SetImage(sprite_sheet);
		root_icon->m_sprite.SetSource(277, 43, 26, 16);
		root_icon->m_transform.SetPosition(40, 810);
	}
	Icon* new_icon = root_icon;
	for (int i = 1; i < lives; i++)
	{
        float distance = 40;
		new_icon->left_ptr = new Icon();
		new_icon = new_icon->left_ptr;
		
		new_icon->m_sprite.SetImage(sprite_sheet);
		new_icon->m_sprite.SetSource(277, 43, 26, 16);
		new_icon->m_transform.SetPosition(40 + distance * i, 810);
	}

}
void Interface::Livesdisplay::Render(RenderManager& renderManager,int lives)
{
	Icon* temp_icon;
	temp_icon = root_icon;
	for (int i = 0; i < lives; i++)
	{
		renderManager.Render(temp_icon->m_sprite, temp_icon->m_transform);
		temp_icon = temp_icon->left_ptr;
	}

}
void Interface::Livesdisplay::Update(int lives)
{
	/*Icon* temp_icon;
	temp_icon = root_icon;
		for (int i = 0; i + lives < 3; i++)
		{
	    	temp_icon->m_sprite.SetSource(0, 0, 0, 0);
			temp_icon = temp_icon->left_ptr;
		}*/
}
Interface::Score_display::Score_display() : root_row(nullptr)
{
}
Interface::Score_display::Score_display(Image& sprite_sheet, int score) : root_row(nullptr)
{
	Initialize(sprite_sheet, score);
}
void Interface::Score_display::SetNumber(int number, int row)
{
	Row* temp_row = root_row;
	if (row == 0)
	{
		temp_row = root_row->left_ptr;
	}
	else if (row == 1)
	{
		temp_row = root_row->left_ptr->left_ptr;
	}
	else if (row == 2)
	{
		temp_row = root_row->left_ptr->left_ptr->left_ptr;
	}
	switch (number)
	{
		case 0:
			temp_row->m_sprite.SetSource(156, 81, 10, 15);
			break;
		case 1:
			temp_row->m_sprite.SetSource(178, 80, 6, 15);
			break;
		case 2:
			temp_row->m_sprite.SetSource(194, 81, 10, 15);
			break;
		case 3:
			temp_row->m_sprite.SetSource(213, 81, 10, 15);
			break;
		case 4:
			temp_row->m_sprite.SetSource(233, 81, 10, 15);
			break;
		case 5:
			temp_row->m_sprite.SetSource(253, 81, 10, 15);
			break;
		case 6:
			temp_row->m_sprite.SetSource(155, 99, 10, 15);
			break;
		case 7:
			temp_row->m_sprite.SetSource(273, 81, 10, 15);
			break;
		case 8:
			temp_row->m_sprite.SetSource(175, 99, 10, 15);
			break;
		case 9:
			temp_row->m_sprite.SetSource(193, 99, 10, 15);
			break;
	}
}
void Interface::Score_display::Initialize(Image& sprite_sheet, int score)
{
	m_sprite.SetImage(sprite_sheet);
	m_sprite.SetSource(56, 79, 74, 15);
	m_transform.SetPosition(570, 820);
	if (root_row == nullptr)
	{
		Row* new_row = new Row();
		float distance = 20;
		new_row->m_sprite.SetImage(sprite_sheet);
		new_row->m_sprite.SetSource(156, 81, 10, 14);
		new_row->m_transform.SetPosition(744 - distance, 840 - distance);
		root_row = new_row;
	}
	Row* new_row = root_row;
	for (int i = 1; i < 4; i++)
	{
		new_row->left_ptr = new Row();
		new_row = new_row->left_ptr;
	    float distance = 20;
		new_row->m_sprite.SetImage(sprite_sheet);
    	new_row->m_sprite.SetSource(156, 81, 10, 14);
        new_row->m_transform.SetPosition((744 - distance) - distance * i, 840 - distance);
	}
			

	
}
void Interface::Score_display::Initialize_hi_score(Image& sprite_sheet, int score)
{
	m_sprite.SetImage(sprite_sheet);
	m_sprite.SetSource(8, 79, 122, 15);
	m_transform.SetPosition(320, 820);

	if (root_row == nullptr)
	{
		Row* new_row = new Row();
		float distance = 20;
		new_row->m_sprite.SetImage(sprite_sheet);
		new_row->m_sprite.SetSource(156, 81, 10, 14);
		new_row->m_transform.SetPosition(420 - distance, 840 - distance);
		root_row = new_row;
	}
	Row* new_row = root_row;
	for (int i = 1; i < 4; i++)
	{
		new_row->left_ptr = new Row();
		new_row = new_row->left_ptr;
		float distance = 20;
		new_row->m_sprite.SetImage(sprite_sheet);
		new_row->m_sprite.SetSource(156, 81, 10, 14);
		new_row->m_transform.SetPosition((420 - distance) - distance * i, 840 - distance);
	}
	int row_counter = 0;
	if (score >= 10)
	{
		int temp_score = (score % 100) / 10;
		SetNumber(temp_score, row_counter);
		row_counter++;
	}
	if (score >= 100)
	{
		int temp_score = (score % 1000) / 100;
		SetNumber(temp_score, row_counter);
		row_counter++;
	}
	if (score >= 1000)
	{
		int temp_score = score / 1000;
		SetNumber(temp_score, row_counter);
	}



}
void Interface::Score_display::Render(RenderManager& renderManager)
{
	Row* temp_row;
	temp_row = root_row;
	for (int i = 0; i < 4; i++)
	{
		renderManager.Render(temp_row->m_sprite, temp_row->m_transform);
		temp_row = temp_row->left_ptr;
	}
	renderManager.Render(m_sprite, m_transform);
}
void Interface::Score_display::Update(int score)
{
	int row_counter = 0;
		if (score >= 10)
		{
			int temp_score = (score % 100) / 10;
			SetNumber(temp_score, row_counter);
			row_counter++;
		}
		if(score >= 100)
		{
			int temp_score = (score % 1000) / 100;
			SetNumber(temp_score, row_counter);
			row_counter++;
    	}
		if (score >= 1000)
		{
			int temp_score = score / 1000;
			SetNumber(temp_score, row_counter);
		}

}
Interface::Interface(): m_number(Number::Zero)
{

}
Interface::Interface(Image& sprite_sheet, int lives, int score)
{
	Initialize(sprite_sheet,lives ,score);
}
Interface::Interface(Image& sprite_sheet, int score)
{
	Initialize(sprite_sheet, score);
}
void Interface::Initialize(Image& sprite_sheet,int lives, int score)
{
	m_score_display.Initialize(sprite_sheet, score);
	m_lives_display.Initialize(sprite_sheet, lives);
}

void Interface::Initialize(Image& sprite_sheet, int score)
{
	m_score_display.Initialize_hi_score(sprite_sheet, score);
}

void Interface::Render(RenderManager& renderManager, int lives)
{
	m_score_display.Render(renderManager);
	m_lives_display.Render(renderManager, lives);
}
void Interface::Render(RenderManager& renderManager)
{
	m_score_display.Render(renderManager);
}

void Interface::Update(int score)
{
	m_score_display.Update(score);
	//m_lives_display.Update(lives);
}

Interface::Score_display::Row::Row() : left_ptr(nullptr)
{

}

Interface::Livesdisplay::Icon::Icon() : left_ptr(nullptr)
{
}
