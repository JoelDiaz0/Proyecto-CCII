#pragma once
#include "Traps.h"
class Fallen_Block : public Traps
{
public:
	Fallen_Block();
	~Fallen_Block();
	void update() override;
	void move() override;
	void colision_platform_window(Platform& plt, int width, int height) override;
	void Inicialize(float pos_x, float pos_y, float vsx = 0.f, float vsy = 0.f) override;
private:
	static sf::Texture tex_traps;
};


