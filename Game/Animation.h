#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
public:
	friend class Entity;
	friend class Player;
	friend class Colision;
	Animation();
	~Animation();
	void Initialize(sf::Texture& t1, int tamSprite_x, int tamSprite_y, int num_Sprites, double moveSpeed);
	void Update();
	void Draw(sf::RenderWindow& app);
public:
	sf::Sprite sp;
	sf::IntRect rectSourceSprite;

	double posx{}, posy{};
private:
	double moveSpeed{};
	int tamSprite_x{}, tamSprite_y{}, num_Sprites{};
	sf::Clock time_anim;
};






