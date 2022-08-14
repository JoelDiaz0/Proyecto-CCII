#include "Spear.h"

Spear::Spear() : Traps()
{
}

Spear::~Spear()
{
}

sf::Texture Spear::tex_traps;

void Spear::Inicialize(float pos_x, float pos_y, float vsx, float vsy)
{
	tex_traps.loadFromFile("data\\sprites\\Spear.png");
	this->vsx = vsx;
	this->vsy = vsy;
	this->anim.Initialize(tex_traps, 9, 64, 12, 0.055);
	this->anim.sp.setPosition(pos_x, pos_y);
	no_anim = false;
}

void Spear::update()
{
	anim.Update();
}

void Spear::move()
{
}

void Spear::colision_platform_window(Platform& plt, int width, int height)
{
}


