#include "Demon.h"

Demon::Demon() : Enemy()
{
    life = 30;
}

Demon::~Demon()
{
    for (auto &b : balas)
        delete b;
}

void Demon::attack(sf::RenderWindow& app)
{
    if (time_attack.getElapsedTime().asSeconds() > 7.5)
    {
        isFire = true;
        time_attack.restart();
    }

    if (isFire)
    {
        s1.setVolume(65);
        float extra_vs{ 1.0 };
        for (int i = 1; i < 4; i++)
        {
            s1.play();
            s1.setLoop(true);

            Bullet* bala1 = new Bullet(anim3, 4.5 * extra_vs);
            bala1->scale(2.5, 2.5);
            bala1->angle_sin(15);
            Bullet* bala2 = new Bullet(anim3, 4.5 * extra_vs);
            bala2->scale(2.5, 2.5);
            Bullet* bala3 = new Bullet(anim3, 4.5 * extra_vs);
            bala3->scale(2.5, 2.5);
            bala3->angle_sin(-15);

            if (Ori == 'A')
            {
                anim2.rectSourceSprite.top = anim2.tamSprite_y;
                bala1->position(anim.sp.getPosition().x, anim.sp.getPosition().y + anim2.tamSprite_y / 2);
                bala1->orientacion(false);
                bala2->position(anim.sp.getPosition().x, anim.sp.getPosition().y + anim2.tamSprite_y / 2);
                bala2->orientacion(false);
                bala3->position(anim.sp.getPosition().x, anim.sp.getPosition().y + anim2.tamSprite_y / 2);
                bala3->orientacion(false);
            }
            else
            {
                anim2.rectSourceSprite.top = anim2.tamSprite_y * 0;
                bala1->position(anim.sp.getPosition().x + anim.tamSprite_x, anim.sp.getPosition().y + anim2.tamSprite_y / 2);
                bala2->position(anim.sp.getPosition().x + anim.tamSprite_x, anim.sp.getPosition().y + anim2.tamSprite_y / 2);
                bala3->position(anim.sp.getPosition().x + anim.tamSprite_x, anim.sp.getPosition().y + anim2.tamSprite_y / 2);
            }
            disparo.push_back(bala1);
            disparo.push_back(bala2);
            disparo.push_back(bala3);
            extra_vs += 0.2;
        }

        reload = true;
        isFire = false;
        stop = true;
        wait_attack.restart();
    }

    if (!disparo.empty())
    {
        for (auto &b : disparo)
        {
            b->draw(app);
            b->fire_1();
            b->update();
        }
    }

    if (reload && wait_attack.getElapsedTime().asSeconds() > 1.5)
    {
        if (Ori == 'A')
            anim.rectSourceSprite.top = anim.tamSprite_y;
        else
            anim.rectSourceSprite.top = anim.tamSprite_y * 0;
        reload = false;
        stop = false;
        s1.setLoop(false);
    }
}

void Demon::move()
{
    if (!stop)
        anim.sp.move(vsx, 9.8);
}

void Demon::Draw(sf::RenderWindow& app)
{
    anim.sp.setScale(sf::Vector2f(tam_x, tam_y));
    anim2.sp.setScale(sf::Vector2f(tam_x, tam_y));
    if (!isFire && !reload)
    {
        anim.Draw(app);
        anim.Update();
    }

    if (stop)
    {
        anim2.Draw(app);
        anim2.Update();
    }
}
