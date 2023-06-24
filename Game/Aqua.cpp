#include "Aqua.h"

Aqua::Aqua(float x, float y) : Platform() {
	initialize();
	setPosition(x, y);
}

Aqua::Aqua()
{

}

Aqua::~Aqua() {}

sf::Texture Aqua::tex_platform;

void Aqua::initialize()
{
	tex_platform.loadFromFile("data\\background\\water-graphics.png");
	sp_p.setTexture(tex_platform);
}

void Aqua::generar_bloque_1() //Plataforma grande
{
	recortarSprite(0, 0, 330, 330);
	sp_p.setTextureRect(rect);
}

void Aqua::generar_bloque_2() //Plataforma mediana
{
	recortarSprite(375, 110, 230, 223);
	sp_p.setTextureRect(rect);
}
void Aqua::generar_bloque_3() //Plataforma pequenia
{
	recortarSprite(650, 220, 115, 113);
	sp_p.setTextureRect(rect);
}
void Aqua::generar_bloque_4()	//Columna
{
	recortarSprite(790, 10, 140, 320);
	sp_p.setTextureRect(rect);
}
