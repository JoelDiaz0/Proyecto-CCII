#pragma once
#include "Entity.h"
#include "Enemy.h"
#include "Score.h"
class Player : public Entity
{
public:
	friend class Enemy; //Se necesita para detectar colision entre Jugador y Enemigo
	friend class Puntos; //Se necesita para detectar Colision
	friend class Revivir;
	friend class Muerte;
	friend class Traps;
	friend class Key;
	friend class Portal;
	friend class Platform_Movil;
	Player();
	~Player();
	void draw_1(sf::RenderWindow& app);
	void draw_2(sf::RenderWindow& app);
	void attack_1(sf::RenderWindow& app);
	void attack_2(sf::RenderWindow& app);
	void resusitar(float pos_x,float pos_y);
	void colision_enemy(Enemy& e1);
	void colision_platform(Platform& pl1);
	void colision_windows(int width, int height);	
	Score puntaje;
private:
	void orientacion_p1();
	void move_p1();
	void orientacion_p2();
	void move_p2();
private:
	float vsx_aux;
	bool isFire, jump, waitJump, stop, resucitar;
	sf::Clock time_Jump, wait_Jump, timeFire, time_stop, time_dead;
};



