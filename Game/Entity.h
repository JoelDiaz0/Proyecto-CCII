#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Colision.h"
#include "Platform.h"
#include "Bullet.h"
#include <vector>
#include <iostream>
class Entity
{
public:
	friend class Colision; //Se obtiene acceso al objeto Animacion

	Entity();
	~Entity();
	void Update();
	void Draw(sf::RenderWindow& app);
	void Initialize(Animation& anim,const float& x, const float& y, const float& vs);
	void Initialize(Animation& anim, Animation& anim2, const float& x, const float& y, const float& vs);
	void Initialize(Animation& anim, Animation& anim2, Animation& anim3, const float& x, const float& y, const float& vs);
	void Initialize(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, const float& x, const float& y, const float& vs);
	void Initialize(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, Animation& anim5, const float& x, const float& y, const float& vs);
	void Initialize(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, Animation& anim5, Animation& anim6, const float& x, const float& y, const float& vs);
	void Initialize(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, Animation& anim5, Animation& anim6, Animation& anim7, const float& x, const float& y, const float& vs);
	void cargar_audio(sf::SoundBuffer& sb1);
	void cargar_audio(sf::SoundBuffer& sb1, sf::SoundBuffer& sb2);
	void cargar_audio(sf::SoundBuffer& sb1, sf::SoundBuffer& sb2, sf::SoundBuffer& sb3);
	void setPosition(const float& pos_x, const float& pos_y);
	void setScale(const float& tam_x, const float& tam_y);
	void draw_bullet(sf::RenderWindow& app);
	float getPos_x();
	float getPos_y();
	char getOrientacion();
protected:
	std::vector<Bullet*> balas;
	Animation anim, anim2, anim3, anim4, anim5, anim6, anim7;
	Colision c1;
	sf::Sound s1, s2, s3, dead;
	float vsx, vsy, tam_x, tam_y;
	int life;
	char Ori;
};