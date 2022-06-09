#pragma once
#include <iostream>
#include "Animation.h"


class Entity
{
public:
	Entity();
	~Entity();
	void settings(Animation& anim, double posX, double posY);
	void draw(sf::RenderWindow &app);
	virtual void update();



protected:
	Animation anim;
	std::string name;
	double posX, posY, vx, vy;
	bool life;
};



