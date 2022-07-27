#include "Platform.h"

Platform::Platform()
{
	scale_x = 1.f;
	scale_y = 1.f;
	lock = true;
	Noanim = true;
	sp_p.setPosition(0.f, 0.f);
}

Platform::~Platform()
{
}

void Platform::initialize(sf::Texture& tx)
{
	sp_p.setTexture(tx);
}

void Platform::setScale(float scale_x, float scale_y)
{
	this->scale_x = scale_x;
	this->scale_y = scale_y;
}

void Platform::setPosition(float pos_x, float pos_y)
{
	sp_p.setPosition(pos_x, pos_y);
}

void Platform::recortarSprite(int posx, int posy, int tamx, int tamy)
{
	rect.top = posy;
	rect.left = posx;
	rect.width = tamx;
	rect.height = tamy;
}

void Platform::draw(sf::RenderWindow& app)
{
	if (lock)
	{
		sp_p.setScale(sf::Vector2f(scale_x, scale_y));
		app.draw(sp_p);
	}
}













