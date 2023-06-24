#pragma once
#include "Animation.h"
#include <SFML/Audio.hpp>
class EnemyDeath
{
public:
	EnemyDeath(bool tipo);
	~EnemyDeath();
	void draw(sf::RenderWindow& app);
	void update();
	void set_scale(const float& tam_x, const float& tam_y);
	void set_position(const float& pos_x, const float& pos_y);
	void play_sound_dead();
private:
	static sf::Texture texture_dead;
	static sf::Texture texture_dead_2;
	Animation anim;
	sf::Sound s1;
	sf::SoundBuffer sb1;
};

