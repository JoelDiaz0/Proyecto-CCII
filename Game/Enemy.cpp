#include "Enemy.h"

Enemy::Enemy()
{
	isFire = false;
	reload = false;
	stop = false;
	unaVez = false;
	nombre = "enemigo";
	vsx = 0.f;
	vsy = 0.f;
	tam_x = 1.f;
	tam_y = 1.f;
	Ori = 'D';
	sb0_1.loadFromFile("data\\sound\\damage.ogg");
	s0_1.setBuffer(sb0_1);
	s0_1.setVolume(30.f);
	life = 1;
}

Enemy::~Enemy()
{
}

void Enemy::colision_windows(int width, int height)
{
	if (c1.colision_pantalla_enemy(anim_1.sp, width, height) == 'D')
	{
		anim_1.rectSourceSprite.top = anim_1.tamSprite_y;
		vsx = -vsx;
		Ori = 'A';
	}
	else if (c1.colision_pantalla_enemy(anim_1.sp, width, height) == 'A')
	{
		vsx = -vsx;
		Ori = 'D';
		anim_1.rectSourceSprite.top = anim_1.tamSprite_y * 0;
	}
	else if (c1.colision_pantalla_enemy(anim_1.sp, width, height) == 'W')
		vsy = -vsy;
}

void Enemy::colision_platform(Platform& pl1)
{
	if (pl1.lock)
	{
		c1.colision_platform_enemy(anim_1.sp, pl1.sp_p, vsx, vsy, Ori);

		if (Ori == 'D')
			anim_1.rectSourceSprite.top = anim_1.tamSprite_y * 0;
		else if (Ori == 'A')
			anim_1.rectSourceSprite.top = anim_1.tamSprite_y;
	}
}

void Enemy::colision_player_bullet(Player& p1)
{
	if (life > 0)
	{
		for (auto& b : p1.balas)
		{
			if (c1.colision_entity_entity(anim_1.sp, b->anim.sp) && colision_wait.getElapsedTime().asSeconds() > 0.2)
			{
				if (!b->impact)
				{
					if (b->name == "bala_fuego_1")
					{
						b->impact = true;
						life -= b->damage;
					}
					else if (b->name == "bala_rayo")
						life -= b->damage;
					s0_1.play();
					colision_wait.restart();
				}
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

void Enemy::draw_bullets(sf::RenderWindow& app)
{
	if (!balas.empty())
	{
		for (auto& b : balas)
		{
			if (!b->impact)
			{
				b->draw(app);
				b->update();
				b->move();
			}
		}
	}
}

void Enemy::colision_bullets(Platform& plt, int width, int height)
{
	if (!balas.empty())
	{
		for (auto& b : balas)
		{
			if (!b->impact)
			{
				b->colision_window(width, height);
				b->colision_platform(plt);
			}
		}
	}
}

void Enemy::setScale(float tam_x, float tam_y)
{
	this->tam_x = tam_x;
	this->tam_y = tam_y;
}

void Enemy::setPosition(float pos_x, float pos_y)
{
	anim_1.sp.setPosition(pos_x, pos_y);
}

float Enemy::getPosition_x()
{
	return anim_1.sp.getPosition().x;
}

float Enemy::getPosition_y()
{
	return anim_1.sp.getPosition().y;
}

char Enemy::getOrientacion()
{
	return Ori;
}
