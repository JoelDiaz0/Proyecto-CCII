#include "Suriken.h"

Suriken::Suriken() : Traps()
{
}

Suriken::~Suriken()
{
}

sf::Texture Suriken::tex_traps;

void Suriken::Inicialize(float pos_x, float pos_y, float vsx, float vsy)
{
	tex_traps.loadFromFile("data\\sprites\\suriken.png");
	this->vsx = vsx;
	this->vsy = vsy;
	this->anim.Initialize(tex_traps, 32, 32, 8, 0.015);
	this->anim.sp.setPosition(pos_x, pos_y);
	no_anim = false;
}

void Suriken::update()
{
	anim.Update();
}

void Suriken::move()
{
}

void Suriken::colision_platform_window(Platform& plt, int width, int height)
{
}



