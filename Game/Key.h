#pragma once
#include "Item.h"
class Key : public Item
{
public:
	Key();
	~Key();
	void effect(Player& p1) override;
private:
	static int cantidad;
};


