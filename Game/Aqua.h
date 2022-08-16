#pragma once
#include <iostream>
#include "Platform.h"

class Aqua : public Platform
{
public:
	Aqua(float x, float y);
	~Aqua();
	void initialize();
	void generar_bloque_1();
	void generar_bloque_2();
	void generar_bloque_3();
	void generar_bloque_4();
	void pinchos();
private:
	static sf::Texture tex_platform;
};