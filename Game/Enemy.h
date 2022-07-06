#pragma once
#include "Entity.h"
#include "Colision.h"
#include "Platform.h"
#include "Bullet.h"
#include <iostream>

class Enemy : public Entity
{
public:
	friend class Colision;
	Enemy();
	~Enemy();

	void colision_windows(int width, int height);
	void colision_platform(Platform& pl1);

	virtual void Draw(sf::RenderWindow& app);
	virtual void move();
	virtual void attack(sf::RenderWindow& app);

	bool colision_bullet_entity(Bullet& b1);

	//void colision_end_platform(Platform& plt1, bool more_sprite = false);

protected:
	bool isFire;
	bool reload;
	bool stop;
	std::vector<Bullet*> disparo;
	sf::Clock time_attack;
	sf::Clock wait_attack;
	sf::Clock wait_move;
	sf::Clock stop_move;
};

