#pragma once
#include "Player.h"
class Traps
{
public:
	Traps();
	~Traps();
	virtual void update() = 0;
	virtual void move() = 0;
	virtual void colision_platform_window(Platform& plt, int width, int height) = 0;
	void Inicialize(Animation& anim, float pos_x, float pos_y, float vsx = 0.f, float vsy = 0.f);
	void Inicialize(sf::Texture& t1, float pos_x, float pos_y, float vsx = 0.f, float vsy = 0.f);
	void effect(Player& p1);
	void draw(sf::RenderWindow& app);
	void setGravity(bool gravity);
	void setPosition(float pos_x, float pos_y);
	void setRotate(float angulo);
	void setScale(float tam_x, float tam_y);
	void setOrigin(float origin_x, float origin_y);	
protected:
	Animation anim;
	Colision c1;
	std::string nombre;
	sf::Sprite sp;
	sf::Clock time_wait;
	float tam_x, tam_y, vsx, vsy, origin_x, origin_y;
	bool gravity;
private:
	bool no_anim;
};



