#pragma once
#include "Enemy.h"
class Fungus : public Enemy
{
public:
	Fungus();
	~Fungus();
	void update() override;
	void initialize(float pos_x, float pos_y, float vsx, float vsy) override;
	void move() override;
	void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
private:
	static sf::Texture tex_enemy_1;
	sf::Clock time_attack, wait_attack;
};
