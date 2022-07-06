#pragma once
#include <iostream>
#include "Enemy.h"

class Demon : public Enemy
{
public:
	Demon();
	~Demon();
	void move();
	void attack(sf::RenderWindow& app);
	void Draw(sf::RenderWindow& app);

private:
};
