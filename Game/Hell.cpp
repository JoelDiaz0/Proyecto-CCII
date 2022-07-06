#include "Hell.h"

Hell::Hell() : Platform()
{
}

Hell::~Hell()
{
}

void Hell::generar_bloque_1()
{
	tamanio(0, 0, 76, 33);
	sp_p.setTextureRect(rect);
}

void Hell::generar_bloque_2()
{
	tamanio(0, 33, 95, 16);
	sp_p.setTextureRect(rect);
}

void Hell::generar_bloque_3()
{
	tamanio(0, 49, 32, 64);
	sp_p.setTextureRect(rect);
}

void Hell::generar_bloque_4()
{
	tamanio(0, 0, 34, 44);
	sp_p.setTextureRect(rect);
}

