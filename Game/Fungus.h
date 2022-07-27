#pragma once
#include "Enemy.h"


class Fungus : public Enemy
{
public:
	Fungus();
	~Fungus();
	void move() override;
	void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
};
