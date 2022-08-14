#include "Entity.h"

Entity::Entity()
{
	life = 1;
	tam_x = 1.f;
	tam_y = 1.f;
	vsx = 0.f;
	vsy = 0.f;
	Ori = 'D';
	anim.sp.setPosition(0.f, 0.f);
	anim2.sp.setPosition(0.f, 0.f);
	anim3.sp.setPosition(0.f, 0.f);
	anim4.sp.setPosition(0.f, 0.f);
	anim5.sp.setPosition(0.f, 0.f);
	anim6.sp.setPosition(0.f, 0.f);
}

Entity::~Entity()
{
}

float Entity::getPos_x()
{
	return anim.sp.getPosition().x;
}

float Entity::getPos_y()
{
	return anim.sp.getPosition().y;
}

char Entity::getOrientacion()
{
	return Ori;
}

void Entity::Update()
{
	anim2.sp.setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y);
	anim3.sp.setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y);
	anim4.sp.setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y);
	anim5.sp.setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y);
	anim6.sp.setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y);
}

void Entity::Initialize(Animation& anim, float x, float y, float vs)
{
	this->anim = anim;
	this->vsx = vs;
	this->vsy = vs;
	this->anim.sp.setPosition(x, y);
}

void Entity::Initialize_2(Animation& anim, Animation& anim2, float x, float y, float vs)
{
	this->anim = anim;
	this->anim2 = anim2;
	this->anim3 = anim3;
	this->vsx = vs;
	this->vsy = vs;
	this->anim.sp.setPosition(x, y);
}

void Entity::Initialize_3(Animation& anim, Animation& anim2, Animation& anim3, float x, float y, float vs)
{
	this->anim = anim;
	this->anim2 = anim2;
	this->anim3 = anim3;
	this->vsx = vs;
	this->vsy = vs;
	this->anim.sp.setPosition(x, y);
}

void Entity::Initialize_4(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, float x, float y, float vs)
{
	this->anim = anim;
	this->anim2 = anim2;
	this->anim3 = anim3;
	this->anim4 = anim4;
	this->vsx = vs;
	this->vsy = vs;
	this->anim.sp.setPosition(x, y);
}

void Entity::Initialize_5(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, Animation& anim5, float x, float y, float vs)
{
	this->anim = anim;
	this->anim2 = anim2;
	this->anim3 = anim3;
	this->anim4 = anim4;
	this->anim5 = anim5;
	this->vsx = vs;
	this->vsy = vs;
	this->anim.sp.setPosition(x, y);
}

void Entity::Initialize_6(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, Animation& anim5, Animation& anim6, float x, float y, float vs)
{
	this->anim = anim;
	this->anim2 = anim2;
	this->anim3 = anim3;
	this->anim4 = anim4;
	this->anim5 = anim5;
	this->anim6 = anim6;
	this->vsx = vs;
	this->vsy = vs;
	this->anim.sp.setPosition(x, y);
}


void Entity::Initialize_7(Animation& anim, Animation& anim2, Animation& anim3, Animation& anim4, Animation& anim5, Animation& anim6, Animation& anim7, float x, float y, float vs)
{
	this->anim = anim;
	this->anim2 = anim2;
	this->anim3 = anim3;
	this->anim4 = anim4;
	this->anim5 = anim5;
	this->anim6 = anim6;
	this->anim7 = anim7;
	this->vsx = vs;
	this->vsy = vs;
	this->anim.sp.setPosition(x, y);
}


void Entity::cargar_audio_3(sf::SoundBuffer& sb1, sf::SoundBuffer& sb2, sf::SoundBuffer& sb3)
{
	s1.setBuffer(sb1);
	s2.setBuffer(sb2);
	s3.setBuffer(sb3);
	s1.setVolume(25.f);
	s2.setVolume(35.f);
	s3.setVolume(25.f);
}

void Entity::cargar_audio_2(sf::SoundBuffer& sb1, sf::SoundBuffer& sb2)
{
	s1.setBuffer(sb1);
	s2.setBuffer(sb2);
	s1.setVolume(35.f);
	s2.setVolume(25.f);
}

void Entity::cargar_audio(sf::SoundBuffer& sb1)
{
	s1.setBuffer(sb1);
	s1.setVolume(25.f);
}

void Entity::setScale(float tam_x, float tam_y)
{
	this->tam_x = tam_x;
	this->tam_y = tam_y;
}

void Entity::draw_bullet(sf::RenderWindow& app)
{
	if (!balas.empty())
	{
		for (auto& b : balas)
		{
			b->move();
			b->draw(app);
			b->update();
		}
	}
}

void Entity::Draw(sf::RenderWindow& app)
{
	anim.sp.setScale(sf::Vector2f(tam_x, tam_y));
	anim.Draw(app);
}

void Entity::setPosition(float pos_x, float pos_y)
{
	anim.sp.setPosition(pos_x, pos_y);
}


