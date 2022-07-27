#pragma once
#include "Traps.h"
class Spike : public Traps
{
public:
	Spike();
	~Spike();
	void update() override;
	void move() override;
	void colision_platform_window(Platform& plt, int width, int height) override;
};




