#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <iostream>

class Entity
{
public:
	Entity();
	~Entity();

	virtual void Update();

	void Initialize(Animation& anim, double x, double y, double vs);
	void Draw(sf::RenderWindow& app);
	void Scale(double tam_x, double tam_y);
	void setSpeed_x(double vsx);
	void setSpeed_y(double vsy);
	void move_x();
	void move_y();
	void direcction();

public:
	Animation anim;
protected:
	double vsx, vsy, tam_x, tam_y;
	bool life;
};



