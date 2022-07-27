#pragma once
#include "Traps.h"

class Suriken : public Traps
{
public:
	Suriken();
	~Suriken();
	void update() override;
	void move() override;
	void colision_platform_window(Platform& plt, int width, int height) override;
};