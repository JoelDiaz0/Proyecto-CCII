#include "Player.h"

Player::Player()
{
	name = "jugador";
	source1.x = 1;
	source1.y = Up;
}

Player::~Player()
{
}

void Player::control(sf::Keyboard L, sf::Keyboard R, sf::Keyboard U, sf::Keyboard D)
{
	this->L = L;
	this->R = R;
	this->D = D;
	this->U = U;
}

void Player::update(sf::Event& ev)
{
	if (ev.key.code == sf::Keyboard::Up)
	{
		vy -= 10;
		source1.y = Up;	
	}
		
	else if (ev.key.code == sf::Keyboard::Down)
	{
		vy += 10;
		source1.y = Down;	
	}
	else if (ev.key.code == sf::Keyboard::Left)
	{
		vx -= 10;
		source1.y = Left;	
	}
	else if (ev.key.code == sf::Keyboard::Right)
	{
		vx += 10;
		source1.y = Right;		
	}
}


