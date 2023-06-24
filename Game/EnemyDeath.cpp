#include "EnemyDeath.h"

EnemyDeath::EnemyDeath(bool tipo)
{
	if (tipo) {
		texture_dead.loadFromFile("data\\sprites\\explosion.png");
		this->anim.Initialize(texture_dead, 66, 65, 5, 0.2);
		sb1.loadFromFile("data\\sound\\gore.ogg");
		s1.setBuffer(sb1);
		s1.setVolume(30.f);
	}

	else {
		texture_dead_2.loadFromFile("data\\sprites\\explosion_2.png");
		this->anim.Initialize(texture_dead_2, 34, 35, 4, 0.2);
		sb1.loadFromFile("data\\sound\\explosion_1.ogg");
		s1.setBuffer(sb1);
		s1.setVolume(100.f);
	}
}

EnemyDeath::~EnemyDeath()
{
}

sf::Texture EnemyDeath::texture_dead;
sf::Texture EnemyDeath::texture_dead_2;


void EnemyDeath::draw(sf::RenderWindow& app)
{
	app.draw(anim.sp);
}

void EnemyDeath::update()
{
	anim.Update_Una_Vez();
	anim.Reset();
}

void EnemyDeath::set_scale(const float& tam_x, const float& tam_y)
{
	anim.sp.setScale(tam_x, tam_y);
}

void EnemyDeath::set_position(const float& pos_x, const float& pos_y)
{
	anim.sp.setPosition(pos_x, pos_y);
}

void EnemyDeath::play_sound_dead()
{
	s1.play();
}


