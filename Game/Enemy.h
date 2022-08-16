#pragma once
#include <SFML/Audio.hpp>
#include "Platform.h"
#include "Colision.h"
#include "Player.h"
#include <list>
class Enemy
{
public:
	friend class Player; //Se necesita para la detectar la colision entre Enemigo y Jugador
	friend void borrar_balas(Player& p1, Player& p2, std::vector<Enemy*>& enemigos);
	Enemy();
	~Enemy();
	virtual void Draw(sf::RenderWindow& app) = 0;
	virtual void move() = 0;
	virtual void attack(sf::RenderWindow& app) = 0;
	virtual void update() = 0;
	virtual void initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f) = 0;
	void colision_windows(int width, int height);
	void colision_platform(Platform& pl1);
	void colision_player_bullet(Player& p1);
	void draw_bullets(sf::RenderWindow& app);
	void colision_bullets(Platform& plt, int width, int height);
	void setPosition(float pos_x, float pos_y);
	void setScale(float tam_x, float tam_y);
	float getPosition_x();
	float getPosition_y();
	char getOrientacion();
protected:
	Animation anim_1;
	Colision c1;
	std::string nombre;
	sf::Clock colision_wait;
	std::list<Bullet*> balas;
	sf::Sound s0_1;
	sf::SoundBuffer sb0_1;
	int life;
	char Ori;
	float vsx, vsy, tam_x, tam_y;
	bool isFire, reload, stop, unaVez;
};