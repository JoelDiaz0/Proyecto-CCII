#include "Bullet_Demon.h"

Bullet_Demon::Bullet_Demon() : Bullet()
{
	tipo_bala = TIPO_BALA::DEMONIACO;
	damage = 15;
}

Bullet_Demon::~Bullet_Demon()
{
}

sf::Texture Bullet_Demon::tex_bala;

void Bullet_Demon::Initialize(float vsx, float vsy)
{
	tex_bala.loadFromFile("data\\sprites\\bala_demoniaca.png");
	this->anim.Initialize(tex_bala, 28, 28, 2, 0.075);
	this->vsx = vsx;
}
