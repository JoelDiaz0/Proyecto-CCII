#pragma once
#include "Traps.h"
class Spear : public Traps
{
public:
	Spear();
	~Spear();
	void update() override;
	void move() override;
	void colision_platform_window(Platform& plt, int width, int height) override;
};



