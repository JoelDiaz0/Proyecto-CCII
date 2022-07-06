#include "Bullet.h"

Bullet::Bullet(Animation& anim, float vs)
{
	pos_x = 0;
	pos_y = 0;
	this->anim = anim;
	this->vsx = vs;
	this->vsy = 0.f;
	this->tam_x = 1.f;
	this->tam_y = 1.f;
}

Bullet::~Bullet()
{

}

bool Bullet::colision_window(int width, int height)
{
	return c1.colision_bullet_window(anim.sp, width, height);
}

void Bullet::orientacion(bool ori_derecha, bool more_sprites)
{
	if (!ori_derecha)
		vsx = -vsx;
	if (more_sprites)
		anim.rectSourceSprite.top = anim.tamSprite_y;
}

void Bullet::position(int pos_x, int pos_y)
{
	anim.sp.setPosition(pos_x, pos_y);
}

void Bullet::fire_1()
{
	anim.sp.move(vsx, vsy);
}

void Bullet::angle_sin(int angulo)
{
	vsy = vsx / 3 * sin(angulo);
}

void Bullet::draw(sf::RenderWindow& app)
{
	anim.sp.setScale(tam_x, tam_y);
	app.draw(anim.sp);
}

void Bullet::update()
{
	anim.Update();
}

void Bullet::scale(float tam_x, float tam_y)
{
	this->tam_x = tam_x;
	this->tam_y = tam_y;
}