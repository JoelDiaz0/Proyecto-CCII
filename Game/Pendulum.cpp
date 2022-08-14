#include "Pendulum.h"
 
Pendulum::Pendulum() : Traps()
{
}

Pendulum::~Pendulum()
{
}


sf::Texture Pendulum::tex_traps;

void Pendulum::Inicialize(float pos_x, float pos_y, float vsx, float vsy)
{
	tex_traps.loadFromFile("data\\sprites\\pendulo.png");
	this->vsx = vsx;
	this->vsy = vsy;
	this->anim.Initialize(tex_traps, 178, 300, 2, 0.1);
	this->anim.sp.setPosition(pos_x, pos_y);
	no_anim = false;
}

void Pendulum::update()
{
	anim.sp.setOrigin(origin_x,origin_y);
	anim.Update();
}

void Pendulum::move()
{
	anim.sp.rotate(vsx);

	if (time_wait.getElapsedTime().asSeconds() > 0.1)
	{
		if (anim.sp.getRotation() == 90.f || anim.sp.getRotation() == 270.f)
		{
			vsx = -vsx;
			time_wait.restart();
		}
	}
}

void Pendulum::colision_platform_window(Platform& plt, int width, int height)
{
}


