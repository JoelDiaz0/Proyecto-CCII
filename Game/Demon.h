#pragma once
#include <iostream>
#include "Enemy.h"
class Demon : public Enemy
{
public:
	Demon();
	~Demon();
	void move() override;
	void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
	void update() override;
	void initialize(float pos_x, float pos_y, float vsx, float vsy) override;
private:
	static sf::Texture tex_enemy_1, tex_enemy_2;
	Animation anim_2;
	sf::Sound s1;
	sf::SoundBuffer sb1;
	sf::Clock time_attack, wait_attack;
};