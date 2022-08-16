#include "Punk_2.h"

Punk_2::Punk_2() : Player()
{
}

Punk_2::~Punk_2()
{
}

void Punk_2::initialize(float pos_x, float pos_y, float vsx, float vsy)
{
    t2_idle.loadFromFile("data\\sprites\\p2_idle.png");
    t2_run.loadFromFile("data\\sprites\\p2_run.png");
    t2_attack.loadFromFile("data\\sprites\\p2_attack.png");
    t2_up.loadFromFile("data\\sprites\\p2_up.png");
    t2_jump.loadFromFile("data\\sprites\\p2_jump.png");
    t2_death.loadFromFile("data\\sprites\\p2_death.png");
    sb1.loadFromFile("data\\sound\\attack_fire_1.ogg");
    s1.setBuffer(sb1);
    s1.setVolume(30.f);
    this->anim_1.Initialize(t2_idle, 20, 35, 4, 0.1);
    this->anim_2.Initialize(t2_run, 27, 34, 6, 0.075);
    this->anim_4.Initialize(t2_attack, 28, 35, 6, 0.035);
    this->anim_5.Initialize(t2_up, 26, 36, 5, 0.075);
    this->anim_3.Initialize(t2_jump, 27, 36, 4, 0.075);
    this->anim_6.Initialize(t2_death, 38, 34, 6, 0.08);
    this->vsx = vsx;
    this->vsy = vsy;
    this->anim_1.sp.setPosition(pos_x, pos_y);
}

void Punk_2::draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(tam_x, tam_y);
        anim_2.sp.setScale(tam_x, tam_y);
        anim_3.sp.setScale(tam_x, tam_y);
        anim_4.sp.setScale(tam_x, tam_y);
        anim_5.sp.setScale(tam_x, tam_y);
        anim_6.sp.setScale(tam_x, tam_y);

        isFire = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            anim_3.Draw(app);
            anim_3.Update();
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            anim_2.Draw(app);
            anim_2.Update();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))
        {
            anim_4.Draw(app);
            anim_4.Update();
            isFire = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
        {
            anim_5.Draw(app);
            anim_5.Update();
        }
        else
        {
            if (Ori == 'A')
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y;
            else if (Ori == 'D')
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y * 0;
            anim_1.Draw(app);
            anim_1.Update();
        }
    }
    else
    {
        anim_1.sp.move(0.f, 9.8f);
        anim_6.Update_Una_Vez();
        anim_6.Draw(app);
    }
}

void Punk_2::control()
{
    if (life > 0)
    {
        //MOVIMIENTO
        if (stop == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !jump && !waitJump) //Salto
            {
                jump = true;
                waitJump = true;
            }
        }

        if (jump && waitJump && time_Jump.getElapsedTime().asSeconds() > 0.005)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                anim_1.sp.move(-vsx * 3.f, -vsy * 5.5f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                anim_1.sp.move(vsx * 3.f, -vsy * 5.5f);
            }
            else
            {
                anim_1.sp.move(0.f, -vsy * 5.5f);
            }
            time_Jump.restart();
        }

        if (waitJump && wait_Jump.getElapsedTime().asSeconds() > 0.085)
        {
            jump = false;
            stop = true;
            wait_Jump.restart();
        }

        if (!jump)
        {
            waitJump = false;
            anim_1.sp.move(0.f, vsy * 2.f);
        }

        if (stop == true && time_stop.getElapsedTime().asSeconds() > 0.175)
        {
            stop = false;
            time_stop.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            anim_1.sp.move(-vsx, 0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            anim_1.sp.move(vsx, 0.f);
        }

        //ORIENTACION
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))  //Derecha
        {
            anim_2.rectSourceSprite.top = anim_2.tamSprite_y * 0;
            Ori = 'D';
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))   //Izquierda
        {
            anim_2.rectSourceSprite.top = anim_2.tamSprite_y;
            Ori = 'A';
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))   //Salto
        {
            if (Ori == 'D')
                anim_3.rectSourceSprite.top = anim_3.tamSprite_y * 0;
            else if (Ori == 'A')
                anim_3.rectSourceSprite.top = anim_3.tamSprite_y;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)) //Ataque
        {
            if (Ori == 'D')
            {
                anim_4.rectSourceSprite.top = anim_4.tamSprite_y * 0;
            }
            else if (Ori == 'A')
            {
                anim_4.rectSourceSprite.top = anim_4.tamSprite_y;
            }
        }
        else
        {
            if (Ori == 'D')
            {
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y * 0;
            }
            else if (Ori == 'A')
            {
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y;
            }
        }
    }
}

void Punk_2::attack()
{
    if (life > 0)
    {
        if (isFire && timeFire.getElapsedTime().asSeconds() > 0.5)
        {
            s1.play();
            Bullet* bala1 = new Bullet_Fire();
            bala1->Initialize(6.5f);
            bala1->setScale(2.f, 2.f);

            if (Ori == 'A')
            {
                bala1->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
                bala1->orientacion(false, true);
            }
            else
            {
                bala1->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
                bala1->orientacion(true);
            }
            balas.push_back(bala1);
            timeFire.restart();
        }
    }
}

void Punk_2::revivir(float pos_x, float pos_y)
{
    if (resucitar && time_dead.getElapsedTime().asSeconds() > 8.0)
    {
        s0_2.play();
        anim_1.sp.setPosition(pos_x, pos_y);
        anim_6.Reset();
        life = 1;
        resucitar = false;
        time_dead.restart();
    }
}

void Punk_2::update()
{
    anim_2.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
    anim_3.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
    anim_4.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
    anim_5.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
    anim_6.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
}