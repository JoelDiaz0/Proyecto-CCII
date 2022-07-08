#include "Tatooine.h"

Tatooine::Tatooine() : Platform()
{
}

Tatooine::~Tatooine()
{
}

void Tatooine::generar_bloque_1() //genera plataforma
{
	tamanio(0, 0, 512, 512);
	sp_p.setTextureRect(rect);
}

void Tatooine::generar_bloque_2() //generar_plataforma_fin
{
	tamanio(512, 0, 512, 512);
	sp_p.setTextureRect(rect);
}
void Tatooine::generar_bloque_3()		//generar_plataforma_flo3()
{
	tamanio(0, 640, 768, 128);
	sp_p.setTextureRect(rect);
}
void Tatooine::generar_bloque_4()	//generar_plataforma_flo4()
{
	tamanio(0, 512, 1024, 128);
	sp_p.setTextureRect(rect);
}

void Tatooine::pinchos()
{
	tamanio(0, 768, 256, 175);
	sp_p.setTextureRect(rect);
}
