#include "Scenery_Space.h"

Scenery_Space::Scenery_Space()
{
}

Scenery_Space::~Scenery_Space()
{
}

void Scenery_Space::buildScale() const
{
	escena->setScale(0.7f, 0.7f);
}

void Scenery_Space::buildMusica() const
{
	escena->cargar_musica("data\\music\\level4.ogg");
}

void Scenery_Space::buildFondo() const
{
	escena->cargar_fondo("data\\background\\SpaceSus.jpg");
}

void Scenery_Space::buildVolumen() const
{
	escena->setVolumen(10.f);
}
