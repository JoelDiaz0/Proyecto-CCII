#include "Puntos.h"

Puntos::Puntos() : Item()
{
	nombre = "puntos";
}

Puntos::~Puntos()
{
}

void Puntos::effect(Player& p1)
{
	if (!recogido)
	{
		if (p1.c1.colision_entity_entity(anim.sp, p1.anim.sp)) //Detecta colision entre Item y Jugador
		{
			s1.play();
			//std::cout << "Colision entre PUNTOS y JUGADOR\n";
			recogido = true;
			p1.puntaje.items += 50;
		}
	}
}


