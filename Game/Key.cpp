#include "Key.h"

Key::Key()
{
	nombre = "key";
	cantidad++;
}

Key::~Key()
{
	cantidad--;
}

int Key::cantidad = 0;

void Key::effect(Player& p1)
{
	if (!recogido)
	{
		if (p1.c1.colision_entity_entity(anim.sp, p1.anim.sp)) //Detecta colision entre Item y Jugador
		{
			s1.play();
			recogido = true;
			p1.puntaje.items += 500;
			p1.puntaje.llaves++;
		}
	}
}
