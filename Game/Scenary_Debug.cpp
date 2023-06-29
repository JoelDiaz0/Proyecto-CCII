#include "Scenary_Debug.h"

Scenary_Debug::Scenary_Debug() {}
Scenary_Debug::~Scenary_Debug() {}

void Scenary_Debug::buildScale() const {
	escena->setScale(3.15f, 2.0f);
}

void Scenary_Debug::buildMusica() const
{
	escena->cargar_musica("data\\music\\debug.ogg");
}

void Scenary_Debug::buildFondo() const
{
	escena->cargar_fondo("data\\background\\debug.jpg");
}

void Scenary_Debug::buildVolumen() const
{
	escena->setVolumen(20.f);
}

