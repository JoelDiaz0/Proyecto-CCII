#include "Throwingfire.h"

Throwingfire::Throwingfire() : Enemy()
{
    life = 20;
}

Throwingfire::~Throwingfire()
{
    for (auto b : balas)
        delete b;
}

void Throwingfire::move()
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

void Throwingfire::Draw(sf::RenderWindow& app)
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

void Throwingfire::attack(sf::RenderWindow& app)
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

        Bullet* bala1 = new Bullet(anim2, 7.5);
        bala1->scale(3.f, 3.f);

        if (Ori == 'A')
        {
            bala1->position(anim.sp.getPosition().x, anim.sp.getPosition().y + anim.tamSprite_y / 2);
            bala1->orientacion(false);
        }
        else
        {
            bala1->position(anim.sp.getPosition().x + anim.tamSprite_x, anim.sp.getPosition().y + anim.tamSprite_y / 2);
        }
        disparo.push_back(bala1);
        reload = true;
        isFire = false;
        stop = true;
        wait_attack.restart();
    }

    if (!disparo.empty())
    {
        for (auto b : disparo)
        {
            b->draw(app);
            b->fire_1();
            b->update();
        }
    }

    if (reload && wait_attack.getElapsedTime().asSeconds() > 1.5)
    {
        reload = false;
        stop = false;
    }
}
