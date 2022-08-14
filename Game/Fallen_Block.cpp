#include "Fallen_Block.h"

Fallen_Block::Fallen_Block()
{
}

Fallen_Block::~Fallen_Block()
{
}

sf::Texture Fallen_Block::tex_traps;

void Fallen_Block::Inicialize(float pos_x, float pos_y, float vsx, float vsy)
{
	tex_traps.loadFromFile("data\\sprites\\block.png");
	this->vsx = vsx;
	this->vsy = vsy;
	this->sp.setTexture(tex_traps);
	this->sp.setPosition(pos_x, pos_y);
	no_anim = true;
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


