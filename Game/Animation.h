#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
public:
	friend class Entity;
	Animation();
	~Animation();
	void Initialize(sf::Texture& t1, int tamSprite_x, int tamSprite_y, double moveSpeed);
	void orientation(sf::Event& ev);
	void Update();
	void Draw(sf::RenderWindow& app);
public:
	sf::Sprite sp;
	sf::IntRect rectSourceSprite;
	double posx, posy;
private:
	double moveSpeed;
	int tamSprite_x, tamSprite_y;
	sf::Clock time;
};


