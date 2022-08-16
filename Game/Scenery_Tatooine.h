#pragma once
#include "SceneryBuilder.h"
#include <iostream>

class Scenery_Tatooine : public SceneryBuilder
{
public:
	Scenery_Tatooine();
	~Scenery_Tatooine();
	void buildScale() const;
	void buildMusica() const;
	void buildFondo() const;
	void buildVolumen() const;
};
