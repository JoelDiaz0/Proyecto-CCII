#pragma once
#include "Item.h"
class Muerte : public Item
{
public:
	Muerte();
	~Muerte();
	void effect(Player& p1) override;
    void inicialize(float pos_x, float pos_y) override;
private:
	static sf::Texture tex_item;
	sf::Sound s1;
	sf::SoundBuffer sb1;
};



