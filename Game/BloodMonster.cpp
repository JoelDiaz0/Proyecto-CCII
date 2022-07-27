#include "BloodMonster.h"

BloodMonster::BloodMonster() : Enemy()
{
    nombre = "bloodmonster";
    life = 10;
}

BloodMonster::~BloodMonster()
{
}

void BloodMonster::move()
{
    if (life > 0)
    {
        if (!stop)
            anim.sp.move(vsx, 9.8f);
    }
}

void BloodMonster::attack(sf::RenderWindow& app)
{
}

void BloodMonster::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim.Draw(app);
        anim.Update();
    }
}
