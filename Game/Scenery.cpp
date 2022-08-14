#include "Scenery.h"

Scenary::Scenary()
{
	tam_x = 1.f;
	tam_y = 1.f;
}

Scenary::~Scenary()
{
}

void Scenary::setScale(float tam_x, float tam_y)
{
	this->tam_x = tam_x;
	this->tam_y = tam_y;
}

void Scenary::cargar_fondo(std::string direccion_fondo)
{
	tex_fondo.loadFromFile(direccion_fondo);
	sp_fondo.setTexture(tex_fondo);
}

void Scenary::cargar_musica(std::string direccion_musica)
{
	musica.openFromFile(direccion_musica);
}

void Scenary::setVolumen(float vol)
{
	musica.setVolume(vol);
}
