#pragma once
#include <iostream>
#include "Enemy.h"

class Demon : public Enemy 
{
public:
	Demon();
	~Demon();
	void move() override;
	void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
};
