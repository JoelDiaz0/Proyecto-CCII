#pragma once
#include "Scenery.h"
class SceneryBuilder

{
public:
	SceneryBuilder();
	~SceneryBuilder();
	virtual void buildScale() const = 0;
	virtual void buildMusica() const = 0;
	virtual void buildFondo() const = 0;
	virtual void buildVolumen() const = 0;
	void draw(sf::RenderWindow& app);
	void reproducir_musica();
	void stop_music();
protected:
	Scenary* escena;
	bool unaVez;
};



