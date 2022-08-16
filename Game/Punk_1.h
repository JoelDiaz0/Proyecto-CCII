#pragma once
#include "Player.h"
#include "Bullet_Thunder.h"
class Punk_1 : public Player
{
public:
	Punk_1();
	~Punk_1();
	void initialize(float pos_x, float pos_y, float vsx, float vsy = 9.8f) override;
	void draw(sf::RenderWindow& app) override;
	void control() override;
	void attack() override;
	void revivir(float pos_x, float pos_y) override;
	void update() override;
private:
	Animation anim_2, anim_3, anim_4, anim_5, anim_6;
	sf::Texture t1_idle, t1_run, t1_attack, t1_up, t1_jump, t1_death;
	sf::SoundBuffer sb1;
	sf::Sound s1;
};