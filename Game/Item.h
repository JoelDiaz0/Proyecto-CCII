#pragma once
#include "Player.h"
class Item
{
public:
	friend class Player; //Se necesita para detectar colision con el jugador
	friend class Platform;
	friend bool terminar_level(std::vector<Item*>& portal);
	Item();
	~Item();
	virtual void inicialize(float pos_x, float pos_y) = 0;
	virtual void effect(Player& p1) = 0;
	void update();
	void draw(sf::RenderWindow& app);
	void setPosition(float pos_x, float pos_y);
	void setScale(float tam_x, float tam_y);
	void unlock_platform(Platform& plt);	
protected:
	Animation anim;
	std::string nombre;
	float tam_x, tam_y;
	bool sound_wait, recogido;
};



