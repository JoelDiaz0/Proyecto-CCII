#include "Fallen_Block.h"

Fallen_Block::Fallen_Block()
{
}

Fallen_Block::~Fallen_Block()
{
}

void Fallen_Block::update()
{
}

void Fallen_Block::move()
{
	sp.move(0.f, vsy);
}

void Fallen_Block::colision_platform_window(Platform& plt, int width, int height)
{
	if (plt.lock)
	{
		if (c1.colision_entity_entity(plt.sp_p, sp) && time_wait.getElapsedTime().asSeconds() > 0.1)
		{
			vsy = -vsy;
			time_wait.restart();
		}	
	}

	if (anim.sp.getPosition().x + anim.tamSprite_x > width || anim.sp.getPosition().y + anim.tamSprite_y > height || anim.sp.getPosition().x < 0 || anim.sp.getPosition().y < 0)
	{
		if (time_wait.getElapsedTime().asSeconds() > 0.1)
		{
			vsy = -vsy;
			time_wait.restart();
		}
	}
}
