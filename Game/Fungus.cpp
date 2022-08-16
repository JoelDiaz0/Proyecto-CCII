#include "Fungus.h"
Fungus::Fungus() : Enemy()
{
	nombre = "fungus";
	life = 10;
}

Fungus::~Fungus()
{
}

sf::Texture Fungus::tex_enemy_1;

void Fungus::initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f)
{
	tex_enemy_1.loadFromFile("data\\sprites\\fungus.png");
	anim_1.Initialize(tex_enemy_1, 17, 20, 3, 0.055);
	this->vsx = vsx;
	this->vsy = vsy;
	anim_1.sp.setPosition(pos_x, pos_y);
}

void Fungus::update()
{
}

void Fungus::attack(sf::RenderWindow& app)
{
	if (life > 0)
	{
		if (time_attack.getElapsedTime().asSeconds() > 3.5)
		{
			isFire = true;
			time_attack.restart();
			wait_attack.restart();
		}

		if (isFire && wait_attack.getElapsedTime().asSeconds() > 0.2)
			isFire = false;
	}
}

void Fungus::move()
{
	if (life > 0)
	{
		if (!isFire)
			anim_1.sp.move(vsx, vsy * 2);
		else if (isFire)
			anim_1.sp.move(vsx * 2.f, -vsy * 3);
	}
}

void Fungus::Draw(sf::RenderWindow& app)
{
	if (life > 0)
	{
		anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
		anim_1.Draw(app);
		anim_1.Update();
	}
}
