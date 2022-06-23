#include "Platform.h"

Platform::Platform(sf::Texture& t)
{
	sp_p.setTexture(t);
	scale_x = 1.f;
	scale_y = 1.f;
}

Platform::~Platform()
{

}


void Platform::scale_platform(float scale_x, float scale_y)
{
	this->scale_x = scale_x;
	this->scale_y = scale_y;
}

void Platform::tamanio(int posx, int posy, int tamx, int tamy)
{
	rect.top = posx;
	rect.left = posy;
	rect.width = tamx;
	rect.height = tamy;
}

void Platform::generar_tierra()
{
	tamanio(0, 0, 47, 48);
	sp_p.setTextureRect(rect);
	sp_p.setPosition(0, 380);
}

void Platform::draw(sf::RenderWindow& app)
{
	sp_p.setScale(sf::Vector2f(scale_x, scale_y));
	app.draw(sp_p);
}

