#include "Muerte.h"

Muerte::Muerte() : Item()
{
	nombre = "muerte";
}

Muerte::~Muerte()
{
}

void Muerte::effect(Player& p1)
{
	if (!recogido)
	{
		if (p1.c1.colision_entity_entity(anim.sp, p1.anim.sp)) //Detecta colision entre Item y Jugador
		{
			s1.play();
			p1.s2.play();
			recogido = true;
			//std::cout << "Colision entre MUERTE y JUGADOR\n";
			p1.puntaje.muertes++;
			p1.life--;
		}
	}
}

