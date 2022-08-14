#include "Bullet_Fire.h"

Bullet_Fire::Bullet_Fire() : Bullet()
{
}

Bullet_Fire::~Bullet_Fire()
{
}

sf::Texture Bullet_Fire::tex_bala;

void Bullet_Fire::Initialize(float vsx, float vsy)
{
	tex_bala.loadFromFile("data\\sprites\\buller_fire_1.png");
	this->anim.Initialize(tex_bala, 18, 30, 3, 0.075);
	this->vsx = vsx;
}
