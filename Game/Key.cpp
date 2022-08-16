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
sf::Texture Key::tex_item;

void Key::inicialize(float pos_x, float pos_y)
{
	tex_item.loadFromFile("data\\sprites\\llave.png");
	this->anim = anim;
	this->anim.Initialize(tex_item, 35, 100, 2, 0.15);
	this->anim.sp.setPosition(pos_x, pos_y);
	sb1.loadFromFile("data\\sound\\llave.ogg");
	s1.setBuffer(sb1);
	s1.setVolume(25.f);
}

void Key::effect(Player& p1)
{
	if (!recogido)
	{
		if (p1.c1.colision_entity_entity(anim.sp, p1.anim_1.sp)) //Detecta colision entre Item y Jugador
		{
			s1.play();
			recogido = true;
			p1.puntaje.items += 500;
			p1.puntaje.llaves++;
		}
	}
}


