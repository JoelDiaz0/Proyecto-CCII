#include "Mallet.h"

Mallet::Mallet() : Traps()
{
}

Mallet::~Mallet()
{
}

void Mallet::update()
{
	anim.sp.setOrigin(origin_x,origin_y);
	anim.Update();
}

void Mallet::move()
{
	anim.sp.rotate(vsx);
}

void Mallet::colision_platform_window(Platform& plt, int width, int height)
{
}
