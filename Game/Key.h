#pragma once
#include "Item.h"
class Key : public Item
{
public:
	Key();
	~Key();
	void effect(Player& p1) override;
	void inicialize(float pos_x, float pos_y) override;
private:
	static int cantidad;
	static sf::Texture tex_item;
	sf::Sound s1;
	sf::SoundBuffer sb1;
};


