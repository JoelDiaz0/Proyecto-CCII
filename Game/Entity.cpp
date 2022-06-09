#include "Entity.h"

Entity::Entity()
{
	life = true;
	vx = 0.0;
	vy = 0.0;
}

Entity::~Entity()
{
}

void Entity::settings(Animation& anim, double posX, double posY)
{
	this->anim = anim;
	this->posX = posX;
	this->posY = posY;
}

void Entity::draw(sf::RenderWindow &app)
{
	anim.sp.setPosition(posX + vx, posY + vy);
	app.draw(anim.sp);
}

void Entity::update()
{
}