#pragma once
#include "Item.h"
class Portal : public Item
{
public:
	Portal();
	~Portal();
	virtual void effect(Player& p1);
	virtual void inicialize(float pos_x, float pos_y);
private:
	static sf::Texture tex_item;
	sf::Sound s1;
	sf::SoundBuffer sb1;
};



