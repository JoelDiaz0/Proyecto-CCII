#pragma once
#include "Traps.h"
class Platform_Movil : public Traps
{
public:
	friend class Player; //Colision con jugador
	Platform_Movil();
	~Platform_Movil();
	void update() override;
	void move() override;
	void colision_platform_window(Platform& plt, int width, int height) override;
};



