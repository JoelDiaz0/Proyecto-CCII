#pragma once
#include <SFML/Audio.hpp>
#include "Bullet_Fire.h"
#include "Bullet_Thunder.h"
#include "Platform.h"
#include "Colision.h"
#include "Enemy.h"
#include "Score.h"
#include "Aqua.h"
#include <vector>
class Player
{
public:
	friend class Enemy; //Se necesita para detectar colision entre Jugador y Enemigo
	friend class Puntos; //Se necesita para detectar Colision entre Jugador e Items
	friend class Revivir;
	friend class Muerte;
	friend class Traps;
	friend class Key;
	friend class Portal;
	friend class Platform_Movil;
	friend class PuntosSobrecarga;
	friend class PortalEnemy;

	friend void borrar_balas(Player& p1, Player& p2, std::vector<Enemy*>& enemigos);
	friend void ejecutar_nivel(sf::RenderWindow& App, Player* jugador1, Player* jugador2, std::vector<Platform*>& vec_plataformas, std::vector<Platform*>& vec_unlock_plataformas,
		std::vector<Enemy*>& vec_enemigos, std::vector<Traps*>& vec_trampas, std::vector<Item*>& vec_items);

	Player();
	~Player();
	virtual void initialize(float pos_x, float pos_y, float vsx, float vsy = 4.5f) = 0;
	virtual void draw(sf::RenderWindow& app) = 0;
	virtual void update() = 0;
	virtual void control() = 0;
	virtual void attack() = 0;
	virtual void revivir(float pos_x, float pos_y) = 0;
	void draw_bullets(sf::RenderWindow& app);
	void colision_bullets(Platform& plt, int width, int height);
	void colision_enemy(Enemy& e1);
	void colision_platform(Platform& pl1);
	void colision_windows(int width, int height);
	void setScale(float tam_x, float tam_y);
	void setPosition(float pos_x, float pos_y);
	float getPosition_x();
	float getPosition_y();
	char getOrientacion();
	Score puntaje;
	std::vector<Bullet*> balas;

protected:
	Animation anim_1;
	Colision c1;
	sf::Clock time_Jump, wait_Jump, timeFire, time_stop, time_dead;
	sf::Sound s0_1, s0_2;
	sf::SoundBuffer sb0_1, sb0_2;
	float tam_x, tam_y, vsx, vsy, vsx_aux;
	bool isFire, jump, waitJump, stop, resucitar;
	int life;
	char Ori;
};