#pragma once
#include "Bullet.h"
class Bullet_Fire2 : public Bullet
{
public:
	Bullet_Fire2();
	~Bullet_Fire2();
	void Initialize(float vsx, float vsy = 0.f) override;
private:
	static sf::Texture tex_bala;
};



