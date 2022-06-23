#pragma once
#include <iostream>
#include "Player.h"
#include "Platform.h"
#include <SFML/Graphics.hpp>

class Colision
{
public:
	Colision();
	~Colision();

	void colision_pantalla(Player& e1);
	void colision_entidad(Player& p1, Platform& pl1);

private:

};


