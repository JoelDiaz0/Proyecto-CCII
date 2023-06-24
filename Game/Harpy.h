#pragma once
#include "Enemy.h"
class Harpy : public Enemy
{
public:
	Harpy();
	~Harpy();
	void initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f) override;
	void update() override;
	void move() override;
	void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
	int get_puntaje_enemigo() override;
	TIPO_ENEMIGO get_tipo_enemigo() override;
private:
	static sf::Texture tex_enemy_1;
	sf::Clock wait_move;
};



