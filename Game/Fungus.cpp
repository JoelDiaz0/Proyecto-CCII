#include "Fungus.h"
Fungus::Fungus()
{
	life = 5;
}

Fungus::~Fungus()
{
}

void Fungus::attack(sf::RenderWindow& app)
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

void Fungus::move()
{
	if (!isFire)
		anim.sp.move(vsx, vsy * 2);

	else if (isFire)
		anim.sp.move(vsx * 2.f, -vsy * 3);
}

void Fungus::Draw(sf::RenderWindow& app)
{
	anim.sp.setScale(sf::Vector2f(tam_x, tam_y));
	anim.Draw(app);
	anim.Update();
}
