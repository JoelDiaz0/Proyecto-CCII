#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();
	void setControl(sf::Event& ev);
	void Update();
private:
};


