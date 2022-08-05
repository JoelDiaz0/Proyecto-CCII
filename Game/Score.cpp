#include "Score.h"

Score::Score()
{
	muertes = 0;
	enemigos_asesinados = 0;
	llaves = 0;
	items = 0;
	total = 0l;
}

Score::~Score()
{
}

bool Score::operator==(const Score& s1) const
{
	if ((items + enemigos_asesinados * 100) - (muertes * 50) == (s1.items + s1.enemigos_asesinados * 100) - (s1.muertes * 150))
		return true;
	return false;
}

bool Score::operator!=(const Score& s1) const
{
	if ((items + enemigos_asesinados * 100) - (muertes * 50) != (s1.items + s1.enemigos_asesinados * 100) - (s1.muertes * 150))
		return true;
	return false;
}

bool Score::operator<(const Score& s1) const
{
	if ((items + enemigos_asesinados * 100) - (muertes * 50) < (s1.items + s1.enemigos_asesinados * 100) - (s1.muertes * 150))
		return true;
	return false;
}

bool Score::operator>(const Score& s1) const
{
	if ((items + enemigos_asesinados * 100) - (muertes * 50) > (s1.items + s1.enemigos_asesinados * 100) - (s1.muertes * 150))
		return true;
	return false;
}

bool Score::operator<=(const Score& s1) const
{
	if ((items + enemigos_asesinados * 100) - (muertes * 50) <= (s1.items + s1.enemigos_asesinados * 100) - (s1.muertes * 150))
		return true;
	return false;
}

bool Score::operator>=(const Score& s1) const
{
	if ((items + enemigos_asesinados * 100) - (muertes * 50) >= (s1.items + s1.enemigos_asesinados * 100) - (s1.muertes * 150))
		return true;
	return false;
}

long Score::getTotal() { return total; }

auto Score::calculo()
{
	total = ((items + enemigos_asesinados * 100) - (muertes * 50));
	return total;
}

std::ostream& operator<<(std::ostream& o, Score& s1)
{
	o << "Items = " << s1.items << "\nEnemigos Abatidos = " << s1.enemigos_asesinados 
		<< "\nMuertes = " << s1.muertes << "\nLlaves Recogidas = "<< s1.llaves << "\nPuntaje Total: " << 
		"(items + enemigos_asesinados * 100) - (muertes * 50) = " << s1.calculo() << "\n";
	return o;
}
