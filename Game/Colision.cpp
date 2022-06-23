#include "Colision.h"

Colision::Colision()
{
}

Colision::~Colision()
{
}

void Colision::colision_pantalla(Player& e1)
{
	if (e1.anim.sp.getPosition().x < 0.f)
		e1.anim.sp.setPosition(0.f, e1.anim.sp.getPosition().y);

	if (e1.anim.sp.getPosition().y < 0.f)
		e1.anim.sp.setPosition(e1.anim.sp.getPosition().x, 0.f);

	if (e1.anim.sp.getPosition().x + e1.anim.sp.getGlobalBounds().width > 1280)
		e1.anim.sp.setPosition(1280 - e1.anim.sp.getGlobalBounds().width, e1.anim.sp.getPosition().y);

	if (e1.anim.sp.getPosition().y + e1.anim.sp.getGlobalBounds().height > 720)
		e1.anim.sp.setPosition(e1.anim.sp.getPosition().x, 720 - e1.anim.sp.getGlobalBounds().height);
}

void Colision::colision_entidad(Player& p1, Platform& pl1)
{
	if (p1.anim.sp.getPosition().x == pl1.sp_p.getPosition().x)
		p1.anim.sp.setPosition(0.f, p1.anim.sp.getPosition().y);

	if (p1.anim.sp.getPosition().y == pl1.sp_p.getPosition().y)
		p1.anim.sp.setPosition(p1.anim.sp.getPosition().x, 0.f);

	if (p1.anim.sp.getPosition().x + p1.anim.sp.getGlobalBounds().width == pl1.sp_p.getPosition().x);
	p1.anim.sp.setPosition(pl1.sp_p.getPosition().x - p1.anim.sp.getGlobalBounds().width, p1.anim.sp.getPosition().y);

	if (p1.anim.sp.getPosition().y + p1.anim.sp.getGlobalBounds().height == pl1.sp_p.getPosition().y);
	p1.anim.sp.setPosition(p1.anim.sp.getPosition().x, pl1.sp_p.getPosition().x - p1.anim.sp.getGlobalBounds().height);
}
