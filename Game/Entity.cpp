#include "Entity.h"

Entity::Entity()
{
	life = true;
	tam_x = 1;
	tam_y = 1;
	vsx = 0.0;
	vsy = 0.0;
}

Entity::~Entity()
{

}

void Entity::Update()
{
}


void Entity::Initialize(Animation& anim, double x, double y, double vs)
{
	this->anim = anim;
	this->vsx = vs;
	this->vsy = vs;
	anim.sp.setPosition(x, y);
}

void Entity::move_x()
{
	anim.posx += vsx;
}

void Entity::move_y()
{
	anim.posy += vsy;
}

void Entity::setSpeed_x(double vsx)
{
	this->vsx = vsx;
}

void Entity::setSpeed_y(double vsy)
{
	this->vsy = vsy;
}

void Entity::Scale(double tam_x, double tam_y)
{
	this->tam_x = tam_x;
	this->tam_y = tam_y;
}

void Entity::Draw(sf::RenderWindow& app)
{
	anim.sp.setScale(sf::Vector2f(tam_x, tam_y));
	anim.sp.setPosition(anim.posx + vsx, anim.posy + vsy);

	anim.Update();
	anim.Draw(app);
}

void Entity::direcction()
{

}