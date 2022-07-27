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
};


