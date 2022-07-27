#include "Demon.h"

Demon::Demon() : Enemy()
{
    nombre = "demon";
    life = 30;
}

Demon::~Demon()
{
}

void Demon::attack(sf::RenderWindow& app)
{
    if (life > 0)
    {
        if (time_attack.getElapsedTime().asSeconds() > 7.5)
        {
            isFire = true;
            time_attack.restart();
        }
        if (isFire)
        {
            s2.setVolume(65);
            float extra_vs{ 1.0f };
            for (int i = 1; i < 4; i++)
            {
                s2.play();
                s2.setLoop(true);
                Bullet* bala1 = new Bullet(anim3, 4.5f * extra_vs);
                bala1->setScale(2.5f, 2.5f);
                bala1->setAngle_sin(15);
                Bullet* bala2 = new Bullet(anim3, 4.5f * extra_vs);
                bala2->setScale(2.5f, 2.5f);
                Bullet* bala3 = new Bullet(anim3, 4.5f * extra_vs);
                bala3->setScale(2.5f, 2.5f);
                bala3->setAngle_sin(-15);
                if (Ori == 'A')
                {
                    anim2.rectSourceSprite.top = anim2.tamSprite_y;
                    bala1->setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y + anim2.tamSprite_y / 2.f);
                    bala1->orientacion(false);
                    bala2->setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y + anim2.tamSprite_y / 2.f);
                    bala2->orientacion(false);
                    bala3->setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y + anim2.tamSprite_y / 2.f);
                    bala3->orientacion(false);
                }
                else
                {
                    anim2.rectSourceSprite.top = anim2.tamSprite_y * 0;
                    bala1->setPosition(anim.sp.getPosition().x + anim.tamSprite_x, anim.sp.getPosition().y + anim2.tamSprite_y / 2.f);
                    bala2->setPosition(anim.sp.getPosition().x + anim.tamSprite_x, anim.sp.getPosition().y + anim2.tamSprite_y / 2.f);
                    bala3->setPosition(anim.sp.getPosition().x + anim.tamSprite_x, anim.sp.getPosition().y + anim2.tamSprite_y / 2.f);
                }
                balas.push_back(bala1);
                balas.push_back(bala2);
                balas.push_back(bala3);
                extra_vs += 0.2f;
            }
            reload = true;
            isFire = false;
            stop = true;
            wait_attack.restart();
        }

        if (reload && wait_attack.getElapsedTime().asSeconds() > 1.5)
        {
            if (Ori == 'A')
                anim.rectSourceSprite.top = anim.tamSprite_y;
            else
                anim.rectSourceSprite.top = anim.tamSprite_y * 0;
            reload = false;
            stop = false;
            s2.setLoop(false);
        }
    }
}

void Demon::move()
{
    if (life > 0)
    {
        if (!stop)
            anim.sp.move(vsx, 9.8f);
    }
}

void Demon::Draw(sf::RenderWindow& app)
{
    if (life > 0)
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
}
