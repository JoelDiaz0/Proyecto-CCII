#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
public:	
	friend class Entity;
	Animation();
	Animation(sf::Texture& t);
	~Animation();
	void config(sf::Event &ev1);
	void update(double tamTexture,double tamTotalTexture,int x, int y, int w, int h, double extra, bool c1 = false);
	void update2(double tamTexture, double tamTotalTexture, int x, int y, int w, int h, double extra,bool c1);
	void draw(sf::RenderWindow& r);

public:
	enum Direction { Down, Left, Right, Up };
	sf::Vector2i source;
	sf::Sprite sp;
private:

};


