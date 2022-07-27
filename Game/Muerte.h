#pragma once
#include "Item.h"
class Muerte : public Item
{
public:
	Muerte();
	~Muerte();
	void effect(Player& p1) override;
};



