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
	friend class PuntosSobrecarga;
	bool operator==(const Score& t1) const;
	bool operator!=(const Score& t1) const;
	bool operator<(const Score& t1) const;
	bool operator>(const Score& t1) const;
	bool operator<=(const Score& t1) const;
	bool operator>=(const Score& t1) const;
	friend std::ostream& operator<<(std::ostream& o, Score& s1);
	int getTotal();
	int get_puntos_enemigos();
	void set_puntos_enemigos(int puntos_enemigos);
	int get_enemigos_asesinados() const;
	void set_enemigos_asesinados(const int& enemigos_asesinados);

private:
	int muertes;
	int enemigos_asesinados;
	int llaves;
	int items;
	int puntos_enemigos;
};


