#include "Platform_Movil.h"

Platform_Movil::Platform_Movil() : Traps()
{
	tam_x = 1.f;
	tam_y = 1.f;
	vsx = 0.f;
	nombre = "platform_movil";
}

Platform_Movil::~Platform_Movil()
{
}

void Platform_Movil::update()
{
	anim.Update();
}

void Platform_Movil::move()
{
	anim.sp.move(vsx, vsy);
}

void Platform_Movil::colision_platform_window(Platform& plt, int width, int height)
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
