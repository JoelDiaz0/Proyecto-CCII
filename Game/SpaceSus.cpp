#include "SpaceSus.h"

SpaceSus::SpaceSus() : Platform()
{
}

SpaceSus::~SpaceSus()
{
}

sf::Texture SpaceSus::tex_platform;

void SpaceSus::initialize()
{
	tex_platform.loadFromFile("data\\background\\SpaceSus_graphics.png");
	sp_p.setTexture(tex_platform);
}

void SpaceSus::generar_bloque_1()
{
	recortarSprite(256, 160, 32, 32);
	sp_p.setTextureRect(rect);
}

void SpaceSus::generar_bloque_2()
{
	recortarSprite(256, 32, 32, 32);
	sp_p.setTextureRect(rect);
}

void SpaceSus::generar_bloque_3()
{
	recortarSprite(256, 64, 32, 32);
	sp_p.setTextureRect(rect);
}

void SpaceSus::generar_bloque_4()
{
	recortarSprite(128, 256, 32, 32);
	sp_p.setTextureRect(rect);
}



