#include "Hell.h"

Hell::Hell() : Platform()
{
}

Hell::~Hell()
{
}

sf::Texture Hell::tex_platform;

void Hell::initialize()
{
	tex_platform.loadFromFile("data\\background\\hell_graphics.png");
	sp_p.setTexture(tex_platform);
}

void Hell::generar_bloque_1()
{
	recortarSprite(0, 0, 76, 33);
	sp_p.setTextureRect(rect);
}

void Hell::generar_bloque_2()
{
	recortarSprite(0, 33, 32, 16);
	sp_p.setTextureRect(rect);
}

void Hell::generar_bloque_3()
{
	recortarSprite(0, 49, 32, 64);
	sp_p.setTextureRect(rect);
}

void Hell::generar_bloque_4()
{
	recortarSprite(0, 0, 34, 44);
	sp_p.setTextureRect(rect);
}



