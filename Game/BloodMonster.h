#pragma once
#include "Enemy.h"

class BloodMonster : public Enemy
{
public:
	BloodMonster();
	~BloodMonster();
	void move() override;
	void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
	void update() override;
	void initialize(float pos_x, float pos_y, float vsx, float vsy) override;
private:
	static sf::Texture tex_enemy_1;
};