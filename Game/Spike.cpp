#include "Spike.h"

Spike::Spike() : Traps()
{
}

Spike::~Spike()
{
}

sf::Texture Spike::tex_traps;

void Spike::Inicialize(float pos_x, float pos_y, float vsx, float vsy)
{
	tex_traps.loadFromFile("data\\sprites\\spike.png");
	this->vsx = vsx;
	this->vsy = vsy;
	this->anim.Initialize(tex_traps, 32, 14, 10, 0.075);
	this->anim.sp.setPosition(pos_x, pos_y);
	no_anim = false;
}

void Spike::update()
{
	anim.Update();
}

void Spike::move()
{
}

void Spike::colision_platform_window(Platform& plt, int width, int height)
{
}





