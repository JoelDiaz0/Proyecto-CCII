#pragma once
#include <iostream>
#include "Platform.h"

class Tatooine : public Platform
{
public:
	Tatooine();
	~Tatooine();
	void generar_bloque_1();
	void generar_bloque_2();
	void generar_bloque_3();
	void generar_bloque_4();
	void pinchos();

private:
};