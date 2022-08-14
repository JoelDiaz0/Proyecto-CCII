#include "Bullet_Fire2.h"

Bullet_Fire2::Bullet_Fire2()
{
}

Bullet_Fire2::~Bullet_Fire2()
{
}

sf::Texture Bullet_Fire2::tex_bala;

void Bullet_Fire2::Initialize(float vsx, float vsy)
{
	tex_bala.loadFromFile("data\\sprites\\buller_fire_2.png");
	this->anim.Initialize(tex_bala, 18, 32, 3, 0.055);
	this->vsx = vsx;
}
