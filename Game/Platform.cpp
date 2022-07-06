#include "Platform.h"

Platform::Platform()
{
	pos_x = 0.f;
	pos_y = 0.f;
	scale_x = 1.f;
	scale_y = 1.f;
}

Platform::~Platform()
{

}

void Platform::cargar_textura(sf::Texture& tx)
{
	sp_p.setTexture(tx);
}

void Platform::scale_platform(float scale_x, float scale_y)
{
	this->scale_x = scale_x;
	this->scale_y = scale_y;
}
void Platform::position(float pos_x, float pos_y)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
	sp_p.setPosition(this->pos_x, this->pos_y);
}

void Platform::tamanio(int posx, int posy, int tamx, int tamy)
{
	rect.top = posy;
	rect.left = posx;
	rect.width = tamx;
	rect.height = tamy;
}

void Platform::generar_bloque_1()
{
}

void Platform::generar_bloque_2()
{
}

void Platform::generar_bloque_3()
{
}

void Platform::generar_bloque_4()
{
}

void Platform::draw(sf::RenderWindow& app)
{
	sp_p.setScale(sf::Vector2f(scale_x, scale_y));
	app.draw(sp_p);
}






