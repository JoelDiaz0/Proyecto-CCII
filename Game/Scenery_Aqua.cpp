#include "Scenery_Aqua.h"

Scenery_Aqua::Scenery_Aqua() {}
Scenery_Aqua::~Scenery_Aqua() {}

void Scenery_Aqua::buildScale() const {
	escena->setScale(1.0f, 1.0f);
}

void Scenery_Aqua::buildMusica() const
{
	escena->cargar_musica("data\\music\\aqua.ogg");
}

void Scenery_Aqua::buildFondo() const
{
	escena->cargar_fondo("data\\background\\underwater-bg.png");
}

void Scenery_Aqua::buildVolumen() const
{
	escena->setVolumen(40.f);
}

