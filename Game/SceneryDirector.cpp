#include "SceneryDirector.h"

SceneryDirector::SceneryDirector()
{
}

SceneryDirector::~SceneryDirector()
{
}

void SceneryDirector::setBuilder(SceneryBuilder* escenario)
{
	this->crear_escenario = escenario;
}

void SceneryDirector::construir_Scenary()
{
	this->crear_escenario->buildFondo();
	this->crear_escenario->buildMusica();
	this->crear_escenario->buildScale();
	this->crear_escenario->buildVolumen();
}

void SceneryDirector::draw_scenary(sf::RenderWindow& app)
{
	this->crear_escenario->draw(app);
}

void SceneryDirector::reproducir_musica()
{
	this->crear_escenario->reproducir_musica();
}


