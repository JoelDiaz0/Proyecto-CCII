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
	void Initialize(Animation& anim, float x, float y, float vs);
	void Initialize_2(Animation& anim, Animation& anim2, float x, float y, float vs);
	void Initialize_3(Animation& anim, Animation& anim2, Animation& anim3, float x, float y, float vs);
	void Initialize_4(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, float x, float y, float vs);
	void Initialize_5(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, Animation& anim5, float x, float y, float vs);
	void Initialize_6(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, Animation& anim5, Animation& anim6, float x, float y, float vs);
	void Initialize_7(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, Animation& anim5, Animation& anim6, Animation& anim7, float x, float y, float vs);
	void cargar_audio(sf::SoundBuffer& sb1);
	void cargar_audio_2(sf::SoundBuffer& sb1, sf::SoundBuffer& sb2);
	void cargar_audio_3(sf::SoundBuffer& sb1, sf::SoundBuffer& sb2, sf::SoundBuffer& sb3);
	void setPosition(float pos_x, float pos_y);
	void setScale(float tam_x, float tam_y);
	void draw_bullet(sf::RenderWindow& app);
	float getPos_x();
	float getPos_y();
	char getOrientacion();
protected:
	std::vector<Bullet*> balas;
	Animation anim, anim2, anim3, anim4, anim5, anim6, anim7;
	Colision c1;
	sf::Sound s1, s2, s3;
	float vsx, vsy, tam_x, tam_y;
	int life;
	char Ori;
};