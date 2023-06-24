#pragma once
#include "Enemy.h"

class Buceo : public Enemy
{
public:
	Buceo();
	~Buceo();
	void move() override;
	virtual void attack(sf::RenderWindow& app) override;
	void Draw(sf::RenderWindow& app) override;
	void update() override;
	void initialize(float pos_x, float pos_y, float vsx, float vsy) override;
	int get_puntaje_enemigo() override;
	TIPO_ENEMIGO get_tipo_enemigo() override;
private:
	static sf::Texture tex_enemy_1;
};

