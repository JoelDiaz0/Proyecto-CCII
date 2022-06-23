#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	friend class Colision;
	Player();
	~Player();
	void Update2(sf::RenderWindow& app, bool p);
private:
	void orientacion_p1();
	void move_p1();
	void orientacion_p2();
	void move_p2();
private:
	bool quieto{};
	char Ori{};
};



