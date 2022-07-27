#pragma once
#include "Traps.h"
class Mallet : public Traps
{
public:
	Mallet();
	~Mallet();
	void update() override;
	void move() override;
	void colision_platform_window(Platform& plt, int width, int height) override;
};



