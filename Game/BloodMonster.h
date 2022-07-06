#pragma once
#include "Enemy.h"

class BloodMonster : public Enemy
{
public:
	BloodMonster();
	~BloodMonster();
	void move();
	void attack(sf::SoundBuffer& s1, sf::RenderWindow& app);
	void Draw(sf::RenderWindow& app);
private:

};


