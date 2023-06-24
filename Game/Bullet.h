#pragma once
#include <iostream>
#include "Animation.h"
#include "Colision.h"
#include "Platform.h"
class Bullet
{
public:
	enum class TIPO_BALA { NORMAL = 0, FUEGO_1, FUEGO_2, ELECTRICO, DEMONIACO };
public:
	friend class Enemy;
	friend class Player;
	friend class Entity; //Colision con entidades
	Bullet();
	virtual ~Bullet();
	virtual void Initialize(float vsx, float vsy = 0.f);
	void draw(sf::RenderWindow& app);
	void update();
	void orientacion(bool ori_derecha = true, bool more_sprites = false);
	void move();
	void setPosition(float pos_x, float pos_y);
	void setScale(float tam_x, float tam_y);
	void setAngle_sin(int angulo);
	void colision_window(int width, int height);
	void colision_platform(Platform& plt);
	bool is_impact() const;
protected:
	static sf::Texture tex_bala_normal;
	TIPO_BALA tipo_bala;
	Animation anim;
	Colision c1;
	float vsx, vsy, tam_x, tam_y;
	int damage;
	bool impact;
};