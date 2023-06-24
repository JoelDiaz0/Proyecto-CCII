#include "PuntosSobrecarga.h"

PuntosSobrecarga::PuntosSobrecarga() : Item()
{
	tipo_item = TIPO_ITEM::PUNTOS_SOBRECARGA;
}

PuntosSobrecarga::~PuntosSobrecarga()
{
}

sf::Texture PuntosSobrecarga::tex_item;

void PuntosSobrecarga::inicialize(float pos_x, float pos_y)
{
	tex_item.loadFromFile("data\\sprites\\item_puntos_sobrecarga.png");
	this->anim.Initialize(tex_item, 31, 57, 5, 0.085);
	this->anim.sp.setPosition(pos_x, pos_y);
	sb1.loadFromFile("data\\sound\\puntos_sobrecargar.ogg");
	s1.setBuffer(sb1);
	s1.setVolume(30.f);
}

void PuntosSobrecarga::effect(Player& p1)
{
	if (!recogido)
	{
		if (p1.c1.colision_entity_entity(anim.sp, p1.anim_1.sp)) //Detecta colision entre Item y Jugador
		{
			s1.play();
			recogido = true;
			p1.puntaje.items += 1000;
		}
	}
}