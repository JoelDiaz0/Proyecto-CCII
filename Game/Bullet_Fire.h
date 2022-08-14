#pragma once
#include "Bullet.h"

class Bullet_Fire : public Bullet
{
public:
	Bullet_Fire();
	~Bullet_Fire();
	void Initialize(float vsx, float vsy = 0.f) override;
private:
	static sf::Texture tex_bala;
};



