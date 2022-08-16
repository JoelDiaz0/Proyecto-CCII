#pragma once
#include "SceneryBuilder.h"
#include <iostream>

class Scenery_Aqua : public SceneryBuilder
{
public:
	Scenery_Aqua();
	~Scenery_Aqua();
	void buildScale() const;
	void buildMusica() const;
	void buildFondo() const;
	void buildVolumen() const;
};