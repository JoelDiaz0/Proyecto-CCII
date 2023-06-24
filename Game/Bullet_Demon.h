#pragma once
#include "Bullet.h"
class Bullet_Demon : public Bullet
{
public:
	Bullet_Demon();
	~Bullet_Demon();
	void Initialize(float vsx, float vsy = 0.f) override;
private:
	static sf::Texture tex_bala;
};

