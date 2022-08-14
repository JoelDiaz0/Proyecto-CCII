#pragma once
#include "SceneryBuilder.h"
class SceneryDirector
{
public:
	SceneryDirector();
	~SceneryDirector();
	void setBuilder(SceneryBuilder* escenario);
	void construir_Scenary();
	void draw_scenary(sf::RenderWindow& app);
	void reproducir_musica();
private:
	SceneryBuilder* crear_escenario;
};



