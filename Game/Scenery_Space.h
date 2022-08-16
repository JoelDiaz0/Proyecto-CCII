#pragma once
#include "SceneryBuilder.h"
#include <iostream>

class Scenery_Space : public SceneryBuilder
{
public:
	Scenery_Space();
	~Scenery_Space();
	void buildScale() const;
	void buildMusica() const;
	void buildFondo() const;
	void buildVolumen() const;
};



