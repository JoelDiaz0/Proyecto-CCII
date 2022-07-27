#include "Spike_Run.h"

Spike_Run::Spike_Run() : Traps()
{
}

Spike_Run::~Spike_Run()
{
}

void Spike_Run::update()
{
	anim.Update();
}

void Spike_Run::move()
{
	if (gravity)
	   anim.sp.move(vsx,9.8f);
	else
	   anim.sp.move(vsx, vsy);
}

void Spike_Run::colision_platform_window(Platform& plt, int width, int height)
{
	if (plt.lock)
	{
		if (c1.colision_entity_entity(plt.sp_p, anim.sp))
		{
			if (time_wait.getElapsedTime().asSeconds() > 0.1)
			{
				vsx = -vsx;
				vsy = -vsy;
				time_wait.restart();
			}
		}
	}

	if (anim.sp.getPosition().x + anim.tamSprite_x > width || anim.sp.getPosition().y + anim.tamSprite_y > height || anim.sp.getPosition().x < 0 || anim.sp.getPosition().y < 0)
	{
		if (time_wait.getElapsedTime().asSeconds() > 0.1)
		{
			vsx = -vsx;
			vsy = -vsy;
			time_wait.restart();
		}
	}
}

