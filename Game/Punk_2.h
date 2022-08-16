#pragma once
#include "Player.h"
#include "Bullet_Fire.h"
class Punk_2 : public Player
{
public:
	Punk_2();
	~Punk_2();
	void initialize(float pos_x, float pos_y, float vsx, float vsy = 4.5f) override;
	void draw(sf::RenderWindow& app) override;
	void control() override;
	void attack() override;
	void revivir(float pos_x, float pos_y) override;
	void update() override;
private:
	Animation anim_2, anim_3, anim_4, anim_5, anim_6;
	sf::Texture t2_idle, t2_run, t2_attack, t2_up, t2_jump, t2_death;
	sf::SoundBuffer sb1;
	sf::Sound s1;
};