#pragma once
#include "Enemy.h"
class Harpy : public Enemy
{
public:
	Harpy();
	~Harpy();
	void move() override;
	void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
};



