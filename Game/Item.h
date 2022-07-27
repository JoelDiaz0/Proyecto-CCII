#pragma once
#include "Player.h"

class Item
{
public:
	friend class Player; //Se necesita para detectar colision con el jugador
	friend class Platform;
	Item();
	~Item();
	void inicialize(Animation& anim, float pos_x, float pos_y);
	void update();
	void draw(sf::RenderWindow& app);
	void setPosition(float pos_x, float pos_y);
	void setScale(float tam_x, float tam_y);
	void setAudio(sf::SoundBuffer& sb1);
	void unlock_platform(Platform& plt);
	virtual void effect(Player& p1) = 0;
protected:
	Animation anim;
	sf::Sound s1;
	std::string nombre;
	float tam_x, tam_y;
	bool sound_wait, recogido;
};



