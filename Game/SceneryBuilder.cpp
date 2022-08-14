#include "SceneryBuilder.h"

SceneryBuilder::SceneryBuilder()
{
	escena = new Scenary();
	unaVez = false;
}

SceneryBuilder::~SceneryBuilder()
{
	delete escena;
}

void SceneryBuilder::draw(sf::RenderWindow& app)
{
	escena->sp_fondo.setScale(escena->tam_x, escena->tam_y);
	app.draw(escena->sp_fondo);
}

void SceneryBuilder::reproducir_musica()
{
	if (!unaVez)
		escena->musica.play();
	unaVez = true;
	escena->musica.setLoop(true);
}
