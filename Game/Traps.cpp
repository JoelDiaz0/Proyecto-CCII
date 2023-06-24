#include "Traps.h"

Traps::Traps() 
{
	tam_x = 1.f;
	tam_y = 1.f;
	vsx = 0.f;
	vsy = 0.f;
	origin_x = 0.f;
	origin_y = 0.f;
	no_anim = true;
	gravity = false;
	nombre = "trampa";
}

Traps::~Traps()
{
}

void Traps::draw(sf::RenderWindow& app)
{
	if (!no_anim)
	{
		anim.sp.setScale(tam_x, tam_y);
		app.draw(anim.sp);
	}
	else
	{
		sp.setScale(tam_x, tam_y);
		app.draw(sp);
	}
}

void Traps::setGravity(bool gravity)
{
	this->gravity = gravity;
}

void Traps::setPosition(float pos_x, float pos_y)
{
	if (!no_anim)
		anim.sp.setPosition(pos_x, pos_y);
	else
		sp.setPosition(pos_x, pos_y);
}

void Traps::setRotate(float angulo)
{
	anim.sp.setRotation(angulo);
}

void Traps::setScale(float tam_x, float tam_y)
{
	this->tam_x = tam_x;
	this->tam_y = tam_y;
}

void Traps::setOrigin(float origin_x, float origin_y)
{
	this->origin_x = origin_x;
	this->origin_y = origin_y;
}

int Traps::get_size_sprite_x() const
{
	return anim.sp.getTextureRect().width;
}

int Traps::get_size_sprite_y() const
{
	return anim.sp.getTextureRect().height;
}


void Traps::effect(Player& p1)
{
	if (!no_anim)
	{
		if (nombre == "trampa")
		{
			if (p1.life > 0)
			{
				if (c1.colision_entity_entity(anim.sp, p1.anim_1.sp))
				{
					p1.s0_1.play();
					p1.life--;
					p1.puntaje.muertes++;
					p1.resucitar = true;
					p1.time_dead.restart();
				}
			}
		}
		else
			c1.colision_platformMovil_player(p1.anim_1.sp, anim.sp);
	}
	else
	{
		if (nombre == "trampa")
		{
			if (p1.life > 0)
			{
				if (c1.colision_entity_entity(sp, p1.anim_1.sp))
				{
					p1.s0_1.play();
					p1.life--;
					p1.puntaje.muertes++;
					p1.resucitar = true;
					p1.time_dead.restart();
				}
			}
		}
		else
			c1.colision_platformMovil_player(p1.anim_1.sp, sp);
	}
}


