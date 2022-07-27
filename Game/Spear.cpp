#include "Spear.h"

Spear::Spear() : Traps()
{
}

Spear::~Spear()
{
}

void Spear::update()
{
	anim.Update();
}

void Spear::move()
{
}

void Spear::colision_platform_window(Platform& plt, int width, int height)
{
}
