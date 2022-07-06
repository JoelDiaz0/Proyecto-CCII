#pragma once
#include "Entity.h"
#include "Colision.h"
#include "Platform.h"

class Player : public Entity
{
public:
	friend class Colision;
	Player();
	~Player();

	void draw_1(sf::RenderWindow& app);
	void draw_2(sf::RenderWindow& app);

	void attack_1(sf::RenderWindow& app);
	void attack_2(sf::RenderWindow& app);

	void colision_platform(Platform& pl1);
	void colision_windows(int width, int height);

private:
	void orientacion_p1();
	void move_p1();
	void orientacion_p2();
	void move_p2();
private:
	bool isFire;
	bool jump;
	bool waitJump;
	bool stop;

	sf::Clock time_Jump;
	sf::Clock wait_Jump;
	sf::Clock timeFire;
	sf::Clock time_stop;
};



