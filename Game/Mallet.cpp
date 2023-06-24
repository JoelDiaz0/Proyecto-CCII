#include "Mallet.h"

Mallet::Mallet() : Traps()
{
}

Mallet::~Mallet()
{
}

sf::Texture Mallet::tex_traps;

void Mallet::Inicialize(float pos_x, float pos_y, float vsx, float vsy)
{
	tex_traps.loadFromFile("data\\sprites\\mazo.png");
	this->vsx = vsx;
	this->vsy = vsy;
	this->anim.Initialize(tex_traps, 102, 300, 2, 0.1);
	this->anim.sp.setPosition(pos_x, pos_y);
	this->anim.sp.setOrigin( anim.sp.getOrigin().x + 102/2, anim.sp.getOrigin().y + 300/2);
	no_anim = false;
}

void Mallet::update()
{
	//anim.sp.setOrigin(origin_x,origin_y);
	anim.Update();
}

void Mallet::move()
{
	anim.sp.rotate(vsx);
}

void Mallet::colision_platform_window(Platform& plt, int width, int height)
{
}


