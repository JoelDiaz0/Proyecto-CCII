#include "Scenary_Lluvia.h"

Scenary_Lluvia::Scenary_Lluvia()
{
}

Scenary_Lluvia::~Scenary_Lluvia()
{
}

void Scenary_Lluvia::buildScale() const
{
	escena->setScale(0.7f, 0.67f);
}

void Scenary_Lluvia::buildMusica() const
{
	escena->cargar_musica("data\\music\\the_hell.ogg");
}

void Scenary_Lluvia::buildFondo() const
{
	escena->cargar_fondo("data\\sprites\\nivel_3\\fondo.png");
}

void Scenary_Lluvia::buildVolumen() const
{
	escena->setVolumen(10.f);
}

