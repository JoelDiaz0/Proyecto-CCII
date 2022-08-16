#pragma once
#include "SceneryBuilder.h"
#include <iostream>

class Scenary_Lluvia : public SceneryBuilder
{
public:
	Scenary_Lluvia();
	~Scenary_Lluvia();
	void buildScale() const;
	void buildMusica() const;
	void buildFondo() const;
	void buildVolumen() const;
};

