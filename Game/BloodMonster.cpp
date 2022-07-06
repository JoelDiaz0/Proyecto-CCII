#include "BloodMonster.h"

BloodMonster::BloodMonster()
{
    life = 15;
}

BloodMonster::~BloodMonster()
{
}

void BloodMonster::attack(sf::SoundBuffer& s1, sf::RenderWindow& app)
{
}

void BloodMonster::move()
{
    if (!stop)
        anim.sp.move(vsx, 9.8);
}

void BloodMonster::Draw(sf::RenderWindow& app)
{
    anim.sp.setScale(sf::Vector2f(tam_x, tam_y));
    anim.Draw(app);
    anim.Update();
}
