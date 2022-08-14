#pragma once
#include "Enemy.h"
#include "Bullet_Fire2.h"
class Throwingfire : public Enemy
{
public:
	Throwingfire();
	~Throwingfire();
	void move() override;
	void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
};
