#pragma once
#include "Item.h"
class Puntos : public Item
{
public:
	Puntos();
	~Puntos();
	void effect(Player& p1) override;
};


