#pragma once
#include "Item.h"
class Portal : public Item
{
public:
	Portal();
	~Portal();
	void effect(Player& p1) override;
};



