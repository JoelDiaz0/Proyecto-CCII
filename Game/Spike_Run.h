#pragma once
#include "Traps.h"

class Spike_Run : public Traps
{
public:
	Spike_Run();
	~Spike_Run();
	void update() override;
	void move() override;
	void colision_platform_window(Platform& plt, int width, int height) override;
};
