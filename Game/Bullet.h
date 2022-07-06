#pragma once
#include <iostream>
#include "Animation.h"
#include "Colision.h"

class Bullet
{
public:
	friend class Enemy;
	friend class Player;

	Bullet(Animation& anim, float vs);
	~Bullet();
	void position(int x, int y);
	bool colision_window(int width, int height);
	void scale(float tam_x, float tam_y);
	void fire_1();
	void angle_sin(int angulo);
	void draw(sf::RenderWindow& app);
	void update();
	void orientacion(bool ori_derecha = true, bool more_sprites = false);

private:
	Animation anim;
	float vsx, vsy;
	int pos_x, pos_y;
	float tam_x, tam_y;
	Colision c1;
};

