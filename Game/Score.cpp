#include "Score.h"

Score::Score()
{
	muertes = 0;
	enemigos_asesinados = 0;
	llaves = 0;
	items = 0;
	puntos_enemigos = 0;
}

Score::~Score()
{
}

bool Score::operator==(const Score& s1) const
{
	if (items + puntos_enemigos + 10 * enemigos_asesinados - muertes * 100 == s1.items + s1.puntos_enemigos + 10 * s1.enemigos_asesinados - s1.muertes * 100)
		return true;
	return false;
}

bool Score::operator!=(const Score& s1) const
{
	if (items + puntos_enemigos + 10 * enemigos_asesinados - muertes * 100 != s1.items + s1.puntos_enemigos + 10 * s1.enemigos_asesinados - s1.muertes * 100)
		return true;
	return false;
}

bool Score::operator<(const Score& s1) const
{
	if (items + puntos_enemigos + 10 * enemigos_asesinados - muertes * 100 < s1.items + s1.puntos_enemigos + 10 * s1.enemigos_asesinados - s1.muertes * 100)
		return true;
	return false;
}

bool Score::operator>(const Score& s1) const
{
	if (items + puntos_enemigos + 10 * enemigos_asesinados - muertes * 100 > s1.items + s1.puntos_enemigos + 10 * s1.enemigos_asesinados - s1.muertes * 100)
		return true;
	return false;
}

bool Score::operator<=(const Score& s1) const
{
	if (items + puntos_enemigos + 10 * enemigos_asesinados - muertes * 100 <= s1.items + s1.puntos_enemigos + 10 * s1.enemigos_asesinados - s1.muertes * 100)
		return true;
	return false;
}

bool Score::operator>=(const Score& s1) const
{
	if (items + puntos_enemigos + 10 * enemigos_asesinados - muertes * 100 >= s1.items + s1.puntos_enemigos + 2 * s1.enemigos_asesinados - s1.muertes * 100)
		return true;
	return false;
}

int Score::getTotal() 
{ 
	return items + puntos_enemigos + (10 * enemigos_asesinados) - muertes * 100;
}

int Score::get_puntos_enemigos()
{
	return puntos_enemigos;
}

void Score::set_puntos_enemigos(int puntos_enemigos)
{
	this->puntos_enemigos = puntos_enemigos;
}

int Score::get_enemigos_asesinados() const
{
	return enemigos_asesinados;
}

void Score::set_enemigos_asesinados(const int& enemigos_asesinados)
{
	this->enemigos_asesinados = enemigos_asesinados;
}

std::ostream& operator<<(std::ostream& o, Score& s1)
{
	o << "Items = " << s1.items << "\nEnemigos Abatidos = " << s1.enemigos_asesinados 
		<< "\nMuertes = " << s1.muertes << "\nLlaves Recogidas = "<< s1.llaves << "\nPuntaje Total: " << 
		"(items + enemigos_asesinados * 100) - (muertes * 50) = " << s1.getTotal() << "\n";
	return o;
}
