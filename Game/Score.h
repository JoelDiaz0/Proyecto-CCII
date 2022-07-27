#pragma once
#include <iostream>
class Score
{
public:
	Score();
	~Score();
	friend class Player;
	friend class Enemy;
	friend class Puntos;
	friend class Muerte;
	friend class Traps;
	friend class Key;
	friend class Portal;
	bool operator==(const Score& t1) const;
	bool operator!=(const Score& t1) const;
	bool operator<(const Score& t1) const;
	bool operator>(const Score& t1) const;
	bool operator<=(const Score& t1) const;
	bool operator>=(const Score& t1) const;
	friend std::ostream& operator<<(std::ostream& o, Score& s1);
private:
	auto calculo();
	int muertes;
	int enemigos_asesinados;
	int llaves;
	int items;
	long total;
};


