#include "Enemy.h"

Enemy::Enemy()
{
	isFire = false;
	reload = false;
	stop = false;
	unaVez = false;
	vsx = 0.f;
	vsy = 0.f;
	tam_x = 1.f;
	tam_y = 1.f;
	Ori = 'D';
	sb0_1.loadFromFile("data\\sound\\damage.ogg");
	s0_1.setBuffer(sb0_1);
	s0_1.setVolume(30.f);
	tipo_enemigo = TIPO_ENEMIGO::UNKNOW;
	ultima_bala = ULTIMA_BALA::NONE;
	life = 1;
}

Enemy::~Enemy()
{

}

void Enemy::colision_windows(int width, int height)
{
	if (tipo_enemigo == TIPO_ENEMIGO::BUCEO || tipo_enemigo == TIPO_ENEMIGO::SUBMARINO || tipo_enemigo == TIPO_ENEMIGO::OVNI || tipo_enemigo == TIPO_ENEMIGO::UNKNOW_BALL) {

		if (anim_1.sp.getPosition().x + anim_1.tamSprite_x > width || anim_1.sp.getPosition().x < 0) {
			vsx = -vsx;
		}
		else if (anim_1.sp.getPosition().y + anim_1.tamSprite_y > height || anim_1.sp.getPosition().y < 0) {
			vsy = -vsy;
		}
	}
	else {
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
}

void Enemy::colision_platform(Platform& pl1)
{
	if (pl1.lock && tipo_enemigo != TIPO_ENEMIGO::BUCEO && tipo_enemigo != TIPO_ENEMIGO::SUBMARINO && tipo_enemigo != TIPO_ENEMIGO::UNKNOW_BALL)
	{
		c1.colision_platform_enemy(anim_1.sp, pl1.sp_p, vsx, vsy, Ori);

		if (Ori == 'D')
			anim_1.rectSourceSprite.top = anim_1.tamSprite_y * 0;
		else if (Ori == 'A')
			anim_1.rectSourceSprite.top = anim_1.tamSprite_y;
	}
}

void Enemy::colision_player_bullet(Player& p1, Player& p2)
{
	if (life > 0)
	{
		for (auto& b : p1.balas)
		{
			if (c1.colision_entity_entity(anim_1.sp, b->anim.sp) && colision_wait.getElapsedTime().asSeconds() > 0.2)
			{
				if (!b->impact)
				{
					life -= b->damage;
					ultima_bala = ULTIMA_BALA::PLAYER_1;
					s0_1.play();
					colision_wait.restart();
				}
			}
		}

		for (auto& b : p2.balas)
		{
			if (c1.colision_entity_entity(anim_1.sp, b->anim.sp) && colision_wait.getElapsedTime().asSeconds() > 0.2)
			{
				if (!b->impact)
				{
					life -= b->damage;
					ultima_bala = ULTIMA_BALA::PLAYER_2;
					s0_1.play();
					colision_wait.restart();
					b->impact = true;
				}
			}
		}
	}
}

void Enemy::draw_bullets(sf::RenderWindow& app)
{
	if (!balas.empty())
	{
		for (auto i = balas.begin(); i != balas.end(); i++) {

			if (!(*i)->impact) {
				(*i)->draw(app);
				(*i)->update();
				(*i)->move();
			}

			else {
				delete (*i);
				balas.erase(i);
				break;
			}
		}
	}
}

void Enemy::colision_bullets(Platform& plt, const int& width, const int& height)
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

bool Enemy::is_life() {
	if (life > 0) {
		return true;
	}
	else {
		return false;
	}
}

Enemy::ULTIMA_BALA Enemy::get_ultima_bala()
{
	return ultima_bala;
}

void Enemy::setScale(const float& tam_x, const float& tam_y)
{
	this->tam_x = tam_x;
	this->tam_y = tam_y;
}

int Enemy::get_sprite_size_x() const
{
	return anim_1.sp.getTextureRect().width;
}

int Enemy::get_sprite_size_y() const
{
	return anim_1.sp.getTextureRect().height;
}

void Enemy::setPosition(const float& pos_x, const float& pos_y)
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

float Enemy::get_scale_x() const
{
	return tam_x;
}

float Enemy::get_scale_y() const
{
	return tam_y;
}

char Enemy::getOrientacion()
{
	return Ori;
}
