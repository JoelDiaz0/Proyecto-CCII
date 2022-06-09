#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(sf::Texture& t)
{
	source.x = 1;
	source.y = Up;
	sp.setTexture(t);
}

Animation::~Animation()
{
}

void Animation::config(sf::Event& ev1)
{
	if (ev1.key.code == sf::Keyboard::Up)
		source.y = Up;
	else if (ev1.key.code == sf::Keyboard::Down)
		source.y = Down;
	else if (ev1.key.code == sf::Keyboard::Left)
		source.y = Left;
	else if (ev1.key.code == sf::Keyboard::Right)
		source.y = Right;
}

void Animation::update(double tamTexture, double tamTotalTexture,int x, int y, int w, int h, double extra, bool c1)
{
	source.x++;
	if (source.x * tamTexture >= tamTotalTexture)
		source.x = 0;

	sp.setTextureRect(sf::IntRect((source.x * x) + extra, y , w, h));
}

void Animation::update2(double tamTexture, double tamTotalTexture, int x, int y, int w, int h, double extra, bool c1)
{
	source.x++;
	if (source.x * tamTexture >= tamTotalTexture)
		source.x = 0;

	sp.setTextureRect(sf::IntRect((source.x * x) + extra, source.y * y, w, h));
}

void Animation::draw(sf::RenderWindow& r)
{
	r.draw(sp);
}