#include "Lava.h"

Lava::Lava() : Traps()
{
}

Lava::~Lava()
{
}

sf::Texture Lava::tex_traps;

void Lava::Inicialize(float pos_x, float pos_y, float vsx, float vsy)
{
	tex_traps.loadFromFile("data\\sprites\\lava.png");
	this->vsx = vsx;
	this->vsy = vsy;
	this->anim.Initialize(tex_traps, 64, 13, 2, 0.08);
	this->anim.sp.setPosition(pos_x, pos_y);
	no_anim = false;
}

void Lava::update()
{
	anim.Update();
}

void Lava::move()
{
}

void Lava::colision_platform_window(Platform& plt, int width, int height)
{
}




