#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class Animation
{
public:
	friend class Entity; //Colision
	friend class Player;
	friend class Punk_1;
	friend class Punk_2;
	friend class Enemy;
	friend class Colision;
	friend class Platform_Movil;
	friend class Bullet;
	friend class Throwingfire;
	friend class Demon;
	friend class Fungus;
	friend class BloodMonster;
	friend class Harpy;
	friend class Item;
	friend class Muerte;
	friend class Puntos;
	friend class Key;
	friend class Portal;
	friend class Traps;
	friend class Spike_Run;
	friend class Spear;
	friend class Lava;
	friend class Spike;
	friend class Suriken;
	friend class Mallet;
	friend class Pendulum;
	friend class Fallen_Block;
	Animation();
	~Animation();
	void Initialize(sf::Texture& t1, int tamSprite_x, int tamSprite_y, int num_Sprites, double moveSpeed);
	void Draw(sf::RenderWindow& app);
	void Update();
	void Update_Una_Vez();
	void Reset();
private:
	double moveSpeed{};
	int tamSprite_x{}, tamSprite_y{}, num_Sprites{};
	float posx{}, posy{};
	sf::Clock time_anim;
	sf::Sprite sp;
	sf::IntRect rectSourceSprite;
};






