#include "Portal.h"

Portal::Portal() : Item()
{
	nombre = "portal";
}

Portal::~Portal()
{
}

void Portal::effect(Player& p1)
{
	if (!recogido)
	{
		if (p1.c1.colision_entity_entity(anim.sp, p1.anim.sp)) //Detecta colision entre Item y Jugador
		{
			s1.play();
			recogido = true;
			p1.puntaje.items += 250;
		}
	}
}
