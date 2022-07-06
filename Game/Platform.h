#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Platform
{
public:
	friend class Player;
	friend class Enemy;

	Platform();
	~Platform();

	void cargar_textura(sf::Texture& tx);
	void position(float pos_x, float pos_y);
	void scale_platform(float scale_x, float scale_y);

	virtual void generar_bloque_1();
	virtual void generar_bloque_2();
	virtual void generar_bloque_3();
	virtual void generar_bloque_4();


	void draw(sf::RenderWindow& app);

protected:
	void tamanio(int posx, int posy, int tamx, int tamy);

protected:
	sf::IntRect rect;
	sf::Sprite sp_p;
	float pos_x{}, pos_y{};
	float scale_x{}, scale_y{};
};


