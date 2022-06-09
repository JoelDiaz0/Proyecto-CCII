#pragma once
#include <iostream>
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	void update(sf::Event &ev);
	void control(sf::Keyboard L ,sf::Keyboard R,sf::Keyboard U,sf::Keyboard D);

private:
	bool move;
	sf::Vector2i source1;
	enum Direction { Down, Left, Right, Up };
	sf::Keyboard L, R, U, D;
};


