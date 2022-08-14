#pragma once
#include <iostream>
#include "Animation.h"
#include "Colision.h"
class Bullet
{
public:
	friend class Enemy;
	friend class Player;
	friend class Entity; //Colision con entidades
	Bullet();
	~Bullet();
	virtual void Initialize(float vsx, float vsy = 0.f);
	void draw(sf::RenderWindow& app);
	void update();
	void orientacion(bool ori_derecha = true, bool more_sprites = false);
	void move();
	void setPosition(float pos_x, float pos_y);
	void setScale(float tam_x, float tam_y);	
	void setAngle_sin(int angulo);
	bool colision_window(int width, int height);
protected:
	static sf::Texture tex_bala_normal;
	Animation anim;
	Colision c1;
	float vsx, vsy, tam_x, tam_y;
};

