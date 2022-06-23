#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Platform
{
public:
	friend class Colision;
	Platform(sf::Texture& t);
	~Platform();
	void scale_platform(float scale_x, float scale_y);
	void generar_tierra();
	void draw(sf::RenderWindow& app);
public:
	sf::Sprite sp_p;
private:
	void tamanio(int posx, int posy, int tamx, int tamy);
private:
	sf::IntRect rect;
	float scale_x{}, scale_y{};
};

