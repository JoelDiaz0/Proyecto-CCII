#include "Portal.h"

Portal::Portal() : Item()
{
	nombre = "portal";
}

Portal::~Portal()
{
}

sf::Texture Portal::tex_item;

void Portal::inicialize(float pos_x, float pos_y)
{
	tex_item.loadFromFile("data\\sprites\\portal.png");
	this->anim.Initialize(tex_item, 50, 98, 7, 0.065);
	this->anim.sp.setPosition(pos_x, pos_y);
	sb1.loadFromFile("data\\sound\\portal.ogg");
	s1.setBuffer(sb1);
	s1.setVolume(35.f);
}

void Portal::effect(Player& p1)
{
	if (!recogido)
	{
		if (p1.c1.colision_entity_entity(anim.sp, p1.anim_1.sp)) //Detecta colision entre Item y Jugador
		{
			s1.play();
			recogido = true;
			p1.puntaje.items += 250;
		}
	}
}


