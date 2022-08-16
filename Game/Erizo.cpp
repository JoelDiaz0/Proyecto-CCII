#include "Erizo.h"

Erizo::Erizo(float pos_x, float pos_y) : Traps(){
	setScale(.7, .7);
	Inicialize(pos_x, pos_y);
}

Erizo::~Erizo(){}

sf::Texture Erizo::tex_traps;

void Erizo::Inicialize(float pos_x, float pos_y, float vsx, float vsy){
	tex_traps.loadFromFile("data\\sprites\\sea-urchin.png");
	this->sp.setTexture(tex_traps);
	this->setPosition(pos_x, pos_y);
}

void Erizo::update(){anim.Update();}

void Erizo::move(){}

void Erizo::colision_platform_window(Platform& plt, int width, int height){}