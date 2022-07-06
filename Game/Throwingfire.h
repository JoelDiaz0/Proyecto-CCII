#pragma once
#include "Enemy.h"

class Throwingfire : public Enemy
{
public:
	Throwingfire();
	~Throwingfire();

	void move();
	void attack(sf::RenderWindow& app);
	void Draw(sf::RenderWindow& app);

private:
};
