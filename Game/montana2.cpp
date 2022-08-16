#include "montana2.h"
montana2::montana2() : Platform()
{
}

montana2::~montana2()
{
}

sf::Texture montana2::tex_platform;

void montana2::initialize()
{
	tex_platform.loadFromFile("data\\sprites\\nivel_3\\piso2.png");
	sp_p.setTexture(tex_platform);
}


void montana2::generar_bloque_1()
{
	recortarSprite(0, 0, 48, 48);
	sp_p.setTextureRect(rect);
}

void montana2::generar_bloque_2()
{
	recortarSprite(0, 33, 95, 16);
	sp_p.setTextureRect(rect);
}

void montana2::generar_bloque_3()
{
	recortarSprite(0, 49, 32, 64);
	sp_p.setTextureRect(rect);
}

void montana2::generar_bloque_4()
{
	recortarSprite(0, 0, 34, 44);
	sp_p.setTextureRect(rect);
}
