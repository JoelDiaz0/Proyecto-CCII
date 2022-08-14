#include "Throwingfire.h"

Throwingfire::Throwingfire() : Enemy()
{
    nombre = "throwingfire";
    life = 20;
}

Throwingfire::~Throwingfire()
{
}

void Throwingfire::move()
{
    if (life > 0)
    {
        if (!stop)
        {
            anim.sp.move(vsx, vsy / 3);

            if (wait_move.getElapsedTime().asSeconds() > 0.5)
            {
                vsy = -vsy;
                wait_move.restart();
            }
        }
    }
}

void Throwingfire::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim.sp.setScale(sf::Vector2f(tam_x, tam_y));
        if (!isFire && !reload)
        {
            if (Ori == 'A')
                anim.rectSourceSprite.top = anim.tamSprite_y;
            else
                anim.rectSourceSprite.top = anim.tamSprite_y * 0;
        }
        if (stop)
        {
            if (Ori == 'A')
                anim.rectSourceSprite.top = anim.tamSprite_y * 3;
            else
                anim.rectSourceSprite.top = anim.tamSprite_y * 2;
        }
        anim.Draw(app);
        anim.Update();
    }
}

void Throwingfire::attack(sf::RenderWindow& app)
{
    if (life > 0)
    {
        if (time_attack.getElapsedTime().asSeconds() > 10.0)
        {
            isFire = true;
            time_attack.restart();
        }

        if (isFire)
        {
            s1.setVolume(15);
            s1.play();

            Bullet* bala1 = new Bullet_Fire2();
            bala1->Initialize(7.5f);
            bala1->setScale(3.f, 3.f);

            if (Ori == 'A')
            {
                bala1->setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y + anim.tamSprite_y / 2);
                bala1->orientacion(false);
            }
            else
            {
                bala1->setPosition(anim.sp.getPosition().x + anim.tamSprite_x, anim.sp.getPosition().y + anim.tamSprite_y / 2);
            }
            balas.push_back(bala1);
            reload = true;
            isFire = false;
            stop = true;
            wait_attack.restart();
        }

        if (reload && wait_attack.getElapsedTime().asSeconds() > 1.5)
        {
            reload = false;
            stop = false;
        }
    }
}