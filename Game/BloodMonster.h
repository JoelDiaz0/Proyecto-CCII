#pragma once
#include "Enemy.h"

class BloodMonster : public Enemy
{
public:
	BloodMonster();
	~BloodMonster();
	void move() override;
	void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
};


