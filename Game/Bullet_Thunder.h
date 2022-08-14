#pragma once
#include "Bullet.h"
class Bullet_Thunder : public Bullet
{
public:
	Bullet_Thunder();
	~Bullet_Thunder();
	void Initialize(float vsx, float vsy = 0.f) override;
private:
	static sf::Texture tex_bala;
};



