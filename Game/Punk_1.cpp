#include "Punk_1.h"

Punk_1::Punk_1() : Player()
{
}

Punk_1::~Punk_1()
{
}

void Punk_1::initialize(float pos_x, float pos_y, float vsx, float vsy)
{
    t1_idle.loadFromFile("data\\sprites\\p1_idle.png");
    t1_run.loadFromFile("data\\sprites\\p1_run.png");
    t1_attack.loadFromFile("data\\sprites\\p1_attack.png");
    t1_up.loadFromFile("data\\sprites\\p1_up.png");
    t1_jump.loadFromFile("data\\sprites\\p1_jump.png");
    t1_death.loadFromFile("data\\sprites\\p1_death.png");
    sb1.loadFromFile("data\\sound\\attack_thunder.ogg");
    s1.setBuffer(sb1);
    s1.setVolume(30.f);
    this->anim_1.Initialize(t1_idle, 21, 35, 4, 0.1);;
    this->anim_2.Initialize(t1_run, 33, 33, 6, 0.075);
    this->anim_4.Initialize(t1_attack, 34, 35, 6, 0.035);
    this->anim_5.Initialize(t1_up, 26, 43, 5, 0.075);
    this->anim_3.Initialize(t1_jump, 34, 35, 4, 0.075);
    this->anim_6.Initialize(t1_death, 38, 34, 5, 0.1);
    this->vsx = vsx;
    this->vsy = vsy;
    this->anim_1.sp.setPosition(pos_x, pos_y);
}

void Punk_1::draw(sf::RenderWindow& app)
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            anim_3.Draw(app);
            anim_3.Update_Una_Vez();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            anim_2.Draw(app);
            anim_2.Update();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
        {
            anim_4.Draw(app);
            anim_4.Update();
            isFire = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            anim_5.Draw(app);
            anim_5.Update_Una_Vez();
            if (wait_Jump.getElapsedTime().asSeconds() > 0.1)
            {
                anim_3.Reset();
                wait_Jump.restart();
            }
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

void Punk_1::control()
{
    if (life > 0)
    {
        //MOVIMIENTO
        if (stop == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !jump && !waitJump) //Salto
            {
                jump = true;
                waitJump = true;
            }
        }

        if (jump && waitJump && time_Jump.getElapsedTime().asSeconds() > 0.005)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            {
                anim_1.sp.move(-vsx * 3.f, -vsy * 5.5f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            anim_1.sp.move(-vsx, 0.f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            anim_1.sp.move(vsx, 0.f);
        }

        //ORIENTACION
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))  //Derecha
        {
            anim_2.rectSourceSprite.top = anim_2.tamSprite_y * 0;
            Ori = 'D';
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))   //Izquierda
        {
            anim_2.rectSourceSprite.top = anim_2.tamSprite_y;
            Ori = 'A';
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))   //Salto
        {
            if (Ori == 'D')
            {
                anim_3.rectSourceSprite.top = anim_3.tamSprite_y * 0;
            }
            else if (Ori == 'A')
            {
                anim_3.rectSourceSprite.top = anim_3.tamSprite_y;
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) //Ataque
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

void Punk_1::attack()
{
    if (life > 0)
    {
        if (isFire && timeFire.getElapsedTime().asSeconds() > 1.0)
        {
            s1.play();
            Bullet* bala1 = new Bullet_Thunder;
            bala1->Initialize(7.5f);
            bala1->setScale(3.0f, 2.5f);
            balas.push_back(bala1);
            if (Ori == 'A')
            {
                bala1->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
                bala1->orientacion(false);
            }
            else
                bala1->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
            timeFire.restart();
        }
    }
}

void Punk_1::revivir(float pos_x, float pos_y)
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

void Punk_1::update()
{
    anim_2.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
    anim_3.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
    anim_4.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
    anim_5.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
    anim_6.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
}