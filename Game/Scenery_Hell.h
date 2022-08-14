#pragma once
#include "SceneryBuilder.h"
#include <iostream>

class Scenery_Hell : public SceneryBuilder
{
public:
	Scenery_Hell();
	~Scenery_Hell();
	void buildScale() const;
	void buildMusica() const;
	void buildFondo() const;
	void buildVolumen() const;
};



