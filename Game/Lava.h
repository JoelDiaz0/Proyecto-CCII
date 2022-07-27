#pragma once
#include "Traps.h"
class Lava : public Traps
{
public:
	Lava();
	~Lava();
	void update() override;
	void move() override;
	void colision_platform_window(Platform& plt, int width, int height) override;
};




