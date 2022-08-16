#include "Scenery_Tatooine.h"

Scenery_Tatooine::Scenery_Tatooine()
{
}

Scenery_Tatooine::~Scenery_Tatooine()
{
}

void Scenery_Tatooine::buildScale() const
{
	escena->setScale(1.0f, 1.0f);
}

void Scenery_Tatooine::buildMusica() const
{
	escena->cargar_musica("data\\music\\music-level1.ogg");
}

void Scenery_Tatooine::buildFondo() const
{
	escena->cargar_fondo("data\\background\\tatooine_background.jpg");
}

void Scenery_Tatooine::buildVolumen() const
{
	escena->setVolumen(11.5f);
}
