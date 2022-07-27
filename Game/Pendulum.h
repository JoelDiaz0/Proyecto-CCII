#pragma once
#include "Traps.h"
class Pendulum : public Traps
{
public:
	Pendulum();
	~Pendulum();
	void update() override;
	void move() override;
	void colision_platform_window(Platform& plt, int width, int height) override;
};



