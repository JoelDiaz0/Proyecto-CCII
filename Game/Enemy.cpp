#include "Enemy.h"

Enemy::Enemy() : Entity()
{
	isFire = false;
	reload = false;
	stop = false;
}

Enemy::~Enemy()
{

}

void Enemy::colision_windows(int width, int height)
{
	if (c1.colision_pantalla_enemy(anim.sp, vsx, vsy, width, height) == 'D')
	{
		anim.rectSourceSprite.top = anim.tamSprite_y;
		vsx = -vsx;
		Ori = 'A';
	}

	else if (c1.colision_pantalla_enemy(anim.sp, vsx, vsy, width, height) == 'A')
	{
		vsx = -vsx;
		Ori = 'D';
		anim.rectSourceSprite.top = anim.tamSprite_y * 0;
	}

	else if (c1.colision_pantalla_enemy(anim.sp, vsx, vsy, width, height) == 'W')
		vsy = -vsy;
}

void Enemy::colision_platform(Platform& pl1)
{
	c1.colision_platform_enemy(anim.sp, pl1.sp_p, vsx, vsy, Ori);

	if (Ori == 'D')
		anim.rectSourceSprite.top = anim.tamSprite_y * 0;
	else if (Ori == 'A')
		anim.rectSourceSprite.top = anim.tamSprite_y;
}

bool Enemy::colision_bullet_entity(Bullet& b1)
{
	return c1.colision_entity_entity(anim.sp, b1.anim.sp, b1.vsx, b1.vsy);
}

void Enemy::move()
{
}

void Enemy::attack(sf::RenderWindow& app)
{
}

void Enemy::Draw(sf::RenderWindow& app)
{
}


/*
void Enemy::colision_end_platform(Platform& plt1, bool more_sprite)
{
	if (c1.enemy_final_colision(anim.sp, plt1.sp_p, vsx))
	{
		vsx = -vsx;
		Ori = 'A';
		if (more_sprite)
			anim.rectSourceSprite.top = anim.tamSprite_y * 0;
	}
	if (c1.enemy_final_colision(anim.sp, plt1.sp_p, vsx))
	{
		vsx = -vsx;
		Ori = 'D';
		if(more_sprite)
			anim.rectSourceSprite.top = anim.tamSprite_y;
	}
}
*/

