#pragma once
#include "Entity.h"
#include "Player.h"
class Enemy : public Entity
{
public:
	friend class Player; //Se necesita para la detectar la colision entre Enemigo y Jugador
	Enemy();
	~Enemy();
	void colision_windows(int width, int height);
	void colision_platform(Platform& pl1);
	void colision_player_bullet(Player& p1);
	virtual void Draw(sf::RenderWindow& app) = 0;
	virtual void move() = 0;
	virtual void attack(sf::RenderWindow& app) = 0;
protected:
	bool isFire, reload, stop, unaVez;
	std::string nombre;
	sf::Clock time_attack, wait_move, wait_attack, stop_move, colision_wait;
};

