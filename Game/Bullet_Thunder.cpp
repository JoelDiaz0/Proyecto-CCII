#include "Bullet_Thunder.h"

Bullet_Thunder::Bullet_Thunder() : Bullet()
{
}

Bullet_Thunder::~Bullet_Thunder()
{
}

sf::Texture Bullet_Thunder::tex_bala;

void Bullet_Thunder::Initialize(float vsx, float vsy)
{
	tex_bala.loadFromFile("data\\sprites\\buller_thunder.png");
	this->anim.Initialize(tex_bala, 34, 27, 7, 0.075);
	this->vsx = vsx;
}
