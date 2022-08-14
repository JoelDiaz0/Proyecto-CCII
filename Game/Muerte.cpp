#include "Muerte.h"

Muerte::Muerte() : Item()
{
	nombre = "muerte";
}

Muerte::~Muerte()
{
}

sf::Texture Muerte::tex_item;

void Muerte::inicialize(float pos_x, float pos_y)
{
	tex_item.loadFromFile("data\\sprites\\item_muerte.png");
	this->anim.Initialize(tex_item, 31, 57, 5, 0.085);
	this->anim.sp.setPosition(pos_x, pos_y);
	sb1.loadFromFile("data\\sound\\score.ogg");
	s1.setBuffer(sb1);
	s1.setVolume(30.f);
}

void Muerte::effect(Player& p1)
{
	if (!recogido)
	{
		if (p1.c1.colision_entity_entity(anim.sp, p1.anim.sp)) //Detecta colision entre Item y Jugador
		{
			s1.play();
			recogido = true;
			p1.puntaje.muertes++;
			p1.life--;
		}
	}
}



