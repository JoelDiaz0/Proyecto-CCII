#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <iostream>
class Platform
{
public:
	friend class Player; //Se usa para detectar Colision con jugador
	friend class Enemy;  //Se usa para detectar Colision con enemigos
	friend class Spike_Run; //Se usa para detectar Colision con Trampa Spike_Run
	friend class Fallen_Block; //Se usa para detectar Colision con Trampa Fallen_Block
	friend class Item;
	friend class Platform_Movil;
	Platform();
	~Platform();
	void initialize(sf::Texture& tx);
	void setPosition(float pos_x, float pos_y);
	void setScale(float scale_x, float scale_y);
	void draw(sf::RenderWindow& app);
	virtual void generar_bloque_1() = 0;
	virtual void generar_bloque_2() = 0;
	virtual void generar_bloque_3() = 0;
	virtual void generar_bloque_4() = 0;
protected:
	void recortarSprite(int posx, int posy, int tamx, int tamy);
protected:
	sf::IntRect rect;//recorte
	sf::Sprite sp_p;//sprite
	float scale_x{}, scale_y{};
	bool lock, Noanim;
};


