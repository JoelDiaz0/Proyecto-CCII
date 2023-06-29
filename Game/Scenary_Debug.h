#pragma once
#include "SceneryBuilder.h"
#include <iostream>
class Scenary_Debug : public SceneryBuilder
{
public:
	Scenary_Debug();
	~Scenary_Debug();
	void buildScale() const;
	void buildMusica() const;
	void buildFondo() const;
	void buildVolumen() const;
};

