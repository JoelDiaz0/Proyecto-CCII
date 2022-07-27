#include "Enemy.h"

Enemy::Enemy() : Entity()
{
	isFire = false;
	reload = false;
	stop = false;
	unaVez = false;
	nombre = "enemigo";
}

Enemy::~Enemy()
{
	for (auto& b : balas)
		delete b;
}

void Enemy::colision_windows(int width, int height)
{
	if (c1.colision_pantalla_enemy(anim.sp, width, height) == 'D')
	{
		anim.rectSourceSprite.top = anim.tamSprite_y;
		vsx = -vsx;
		Ori = 'A';
	}
	else if (c1.colision_pantalla_enemy(anim.sp, width, height) == 'A')
	{
		vsx = -vsx;
		Ori = 'D';
		anim.rectSourceSprite.top = anim.tamSprite_y * 0;
	}
	else if (c1.colision_pantalla_enemy(anim.sp, width, height) == 'W')
		vsy = -vsy;
}

void Enemy::colision_platform(Platform& pl1)
{
	if (pl1.lock)
	{
		c1.colision_platform_enemy(anim.sp, pl1.sp_p, vsx, vsy, Ori);

		if (Ori == 'D')
			anim.rectSourceSprite.top = anim.tamSprite_y * 0;
		else if (Ori == 'A')
			anim.rectSourceSprite.top = anim.tamSprite_y;
	}
}

void Enemy::colision_player_bullet(Player& p1)
{
	for (auto& b : p1.balas)
	{
		if (life > 0)
		{
			if (c1.colision_entity_entity(anim.sp, b->anim.sp) && colision_wait.getElapsedTime().asSeconds() > 0.2)
			{
				s1.play();			
				life--;
				colision_wait.restart();
			}
		}
	}
	if (life <= 0 && !unaVez)
	{
		if (nombre == "fungus")
			p1.puntaje.items += 30;
		else if (nombre == "harpy")
			p1.puntaje.items += 75;
		else if (nombre == "bloodmonster")
			p1.puntaje.items += 100;
		else if (nombre == "throwingfire")
			p1.puntaje.items += 200;
		else if (nombre == "demon")
			p1.puntaje.items += 500;
		p1.puntaje.enemigos_asesinados++;
		unaVez = true;
	}
}