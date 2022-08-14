#include "Scenery_Hell.h"

Scenery_Hell::Scenery_Hell()
{
}

Scenery_Hell::~Scenery_Hell()
{
}

void Scenery_Hell::buildScale() const
{
	escena->setScale(0.7f, 0.7f);
}

void Scenery_Hell::buildMusica() const
{
	escena->cargar_musica("data\\music\\the_hell.ogg");
}

void Scenery_Hell::buildFondo() const
{
	escena->cargar_fondo("data\\background\\hell_background.jpg");
}

void Scenery_Hell::buildVolumen() const
{
	escena->setVolumen(10.f);
}
