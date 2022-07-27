#include "Harpy.h"

Harpy::Harpy() : Enemy()
{
    nombre = "harpy";
    life = 5;
}

Harpy::~Harpy()
{
}

void Harpy::move()
{
    if (life > 0)
    {
        if (!stop)
        {
            anim.sp.move(vsx, vsy / 3);
            if (wait_move.getElapsedTime().asSeconds() > 1.5f)
            {
                vsy = -vsy;
                wait_move.restart();
            }
        }
    }
}

void Harpy::attack(sf::RenderWindow& app)
{
}

void Harpy::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim.Draw(app);
        anim.Update();
    }
}
