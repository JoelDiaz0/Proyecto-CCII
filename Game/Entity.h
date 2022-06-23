#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <iostream>

class Entity
{
public:
	friend class Colision;
	Entity();
	~Entity();
	virtual void Update();
	void Initialize(Animation& anim, double x, double y, double vs);
	void Draw(sf::RenderWindow& app);
	void Scale(double tam_x, double tam_y);
public:
	Animation anim;
protected:
	double vsx, vsy, tam_x, tam_y;
	bool life;
protected:
	void gravity();
};



