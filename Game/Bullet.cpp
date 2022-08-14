#include "Bullet.h"

Bullet::Bullet()
{
	this->vsx = 0.f;
	this->vsy = 0.f;
	this->tam_x = 1.f;
	this->tam_y = 1.f;
	this->anim.sp.setPosition(0.f, 0.f);
}

Bullet::~Bullet()
{
}

sf::Texture Bullet::tex_bala_normal;

void Bullet::Initialize(float vsx, float vsy)
{
	tex_bala_normal.loadFromFile("data\\sprites\\bala_2.png");
	this->anim.Initialize(tex_bala_normal, 15, 15, 4, 0.075);
	this->vsx = vsx;
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

void Bullet::setPosition(float pos_x, float pos_y)
{
	anim.sp.setPosition(pos_x, pos_y);
}

void Bullet::move()
{
	anim.sp.move(vsx, vsy);
}

void Bullet::setAngle_sin(int angulo)
{
	vsy = vsx / 3.f * sin(angulo);
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

void Bullet::setScale(float tam_x, float tam_y)
{
	this->tam_x = tam_x;
	this->tam_y = tam_y;
}