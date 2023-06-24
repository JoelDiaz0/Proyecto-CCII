#pragma once
#include <SFML/Audio.hpp>
#include "Platform.h"
#include "Colision.h"
#include "Player.h"
#include <vector>
class Enemy
{
public:
	enum class TIPO_ENEMIGO { UNKNOW = 0, FUNGUS, HARPY, BLOOD_MONSTER, THROWING_FIRE, DEMON, BUCEO, SUBMARINO, ORUGA, OVNI, ALIEN, UNKNOW_BALL };
	enum class ULTIMA_BALA { NONE, PLAYER_1, PLAYER_2 };
public:
	friend class Player; //Se necesita para la detectar la colision entre Enemigo y Jugador
	friend void borrar_balas(Player& p1, Player& p2, std::vector<Enemy*>& enemigos);
	Enemy();
	virtual ~Enemy();
	virtual void Draw(sf::RenderWindow& app) = 0;
	virtual void move() = 0;
	virtual void attack(sf::RenderWindow& app) = 0;
	virtual void update() = 0;
	virtual void initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f) = 0;
	void colision_windows(int width, int height);
	void colision_platform(Platform& pl1);
	void colision_player_bullet(Player& p1, Player& p2);
	void draw_bullets(sf::RenderWindow& app);
	void colision_bullets(Platform& plt, const int& width, const int& height);
	void setPosition(const float& pos_x, const float& pos_y);
	void setScale(const float& tam_x, const float& tam_y);
	int get_sprite_size_x() const;
	int get_sprite_size_y() const;
	float getPosition_x();
	float getPosition_y();
	float get_scale_x() const;
	float get_scale_y() const;
	char getOrientacion();
	bool is_life();
	ULTIMA_BALA get_ultima_bala();
	virtual int get_puntaje_enemigo() = 0;
	virtual TIPO_ENEMIGO get_tipo_enemigo() = 0;
protected:
	Animation anim_1;
	Colision c1;
	TIPO_ENEMIGO tipo_enemigo;
	ULTIMA_BALA ultima_bala;
	sf::Clock colision_wait;
	std::vector<Bullet*> balas;
	sf::Sound s0_1;
	sf::SoundBuffer sb0_1;
	int life;
	char Ori;
	float vsx, vsy, tam_x, tam_y;
	bool isFire, reload, stop, unaVez;
};