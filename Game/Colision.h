#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Colision
{
public:
	Colision();
	~Colision();

	void colision_pantalla_player(sf::Sprite& s1, int width, int height);
	void colision_platform_player(sf::Sprite& s1, sf::Sprite& s2, float& vsx, float& vsy, float vsx_aux);

	char colision_pantalla_enemy(sf::Sprite& s1, float& vsx, float& vsy, int width, int height);
	void colision_platform_enemy(sf::Sprite& s1, sf::Sprite& s2, float& vsx, float& vsy, char& Ori);
	bool enemy_final_colision(sf::Sprite& e1, sf::Sprite& plt1, float& vsx);

	bool colision_entity_entity(sf::Sprite& e1, sf::Sprite e2, float& vsx, float& vsy);
	bool colision_bullet_window(sf::Sprite b1, int width, int height);

private:
	sf::FloatRect nextPos;
};


