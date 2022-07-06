#pragma once
#include "Enemy.h"


class Fungus : public Enemy
{
public:
	Fungus();
	~Fungus();
	void move();
	void attack(sf::RenderWindow& app);
	void Draw(sf::RenderWindow& app);

private:

};
