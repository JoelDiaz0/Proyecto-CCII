#include "Pendulum.h"
 
Pendulum::Pendulum() : Traps()
{
}

Pendulum::~Pendulum()
{
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
