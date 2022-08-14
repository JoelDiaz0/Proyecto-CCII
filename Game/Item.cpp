#include "Item.h"

Item::Item()
{
	tam_x = 1.f;
	tam_y = 1.f;
	recogido = false;
	sound_wait = false;
	nombre = "item";
}

Item::~Item()
{
}

void Item::update()
{
	if (!recogido)
	    anim.Update();
}

void Item::draw(sf::RenderWindow& app)
{
	if (!recogido)
	{
		anim.sp.setScale(tam_x, tam_y);
		app.draw(anim.sp);
	}
}

void Item::setPosition(float pos_x, float pos_y)
{
	anim.sp.setPosition(pos_x, pos_y);
}

void Item::setScale(float tam_x, float tam_y)
{
	this->tam_x = tam_x;
	this->tam_y = tam_y;
}

void Item::unlock_platform(Platform& plt)
{
	if (this->nombre == "key")
	{
		if (recogido)
		{
			plt.lock = false;
		}
	}
}

