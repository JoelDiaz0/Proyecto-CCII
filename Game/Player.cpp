#include "Player.h"

Player::Player() : Entity()
{
    waitJump = false;
    jump = false;
    isFire = false;
    stop = false;
    resucitar = false;
    vsx_aux = vsx;
}

Player::~Player()
{
    for (auto &b : balas)
        delete b;
}

void Player::move_p1() //Player 1
{
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
            anim.sp.move(-vsx * 3.f, -vsy * 5.5f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            anim.sp.move(vsx * 3.f, -vsy * 5.5f);
        }
        else
        {
            anim.sp.move(0.f, -vsy * 5.5f);
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
        anim.sp.move(0.f, vsy * 2.f);
    }

    if (stop == true && time_stop.getElapsedTime().asSeconds() > 0.175)
    {
        stop = false;
        time_stop.restart();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        anim.sp.move(-vsx, 0.f);
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        anim.sp.move(vsx, 0.f);
    }
}

void Player::orientacion_p1() //Player 1
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))  //Derecha
    {
        anim2.rectSourceSprite.top = anim2.tamSprite_y * 0;
        Ori = 'D';
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))   //Izquierda
    {
        anim2.rectSourceSprite.top = anim2.tamSprite_y;
        Ori = 'A';
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))   //Salto
    {
        if (Ori == 'D')
        {
            anim3.rectSourceSprite.top = anim3.tamSprite_y * 0;
        }
        else if (Ori == 'A')
        {
            anim3.rectSourceSprite.top = anim3.tamSprite_y;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl)) //Ataque
    {
        if (Ori == 'D')
        {
            anim4.rectSourceSprite.top = anim4.tamSprite_y * 0;
        }
        else if (Ori == 'A')
        {
            anim4.rectSourceSprite.top = anim4.tamSprite_y;
        }
    }
    else
    {
        if (Ori == 'D')
        {
            anim.rectSourceSprite.top = anim.tamSprite_y * 0;
        }
        else if (Ori == 'A')
        {
            anim.rectSourceSprite.top = anim.tamSprite_y;
        }
    }
}

void Player::attack_1(sf::RenderWindow& app)
{
    if (life > 0)
    {
        if (isFire && timeFire.getElapsedTime().asSeconds() > 1.0)
        {
            s1.setVolume(15);
            s1.play();
            Bullet* bala1 = new Bullet(anim7, 7.5f);
            bala1->setScale(2.5f, 2.5f);

            if (Ori == 'A')
            {
                bala1->setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y);
                bala1->orientacion(false);
            }
            else
                bala1->setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y);
            balas.push_back(bala1);
            timeFire.restart();
        }
    }
}

void Player::move_p2() //Player 2
{
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
            anim.sp.move(-vsx * 3.f, -vsy * 5.5f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            anim.sp.move(vsx * 3.f, -vsy * 5.5f);
        }
        else
        {
            anim.sp.move(0.f, -vsy * 5.5f);
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
        anim.sp.move(0.f, vsy * 2.f);
    }

    if (stop == true && time_stop.getElapsedTime().asSeconds() > 0.175)
    {
        stop = false;
        time_stop.restart();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        anim.sp.move(-vsx, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        anim.sp.move(vsx, 0.f);
    }
}

void Player::orientacion_p2() //Player 2
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))  //Derecha
    {
        anim2.rectSourceSprite.top = anim2.tamSprite_y * 0;
        Ori = 'D';
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))   //Izquierda
    {
        anim2.rectSourceSprite.top = anim2.tamSprite_y;
        Ori = 'A';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))   //Salto
    {
        if (Ori == 'D')
            anim3.rectSourceSprite.top = anim3.tamSprite_y * 0;
        else if (Ori == 'A')
            anim3.rectSourceSprite.top = anim3.tamSprite_y;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl)) //Ataque
    {
        if (Ori == 'D')
        {
            anim4.rectSourceSprite.top = anim4.tamSprite_y * 0;
        }
        else if (Ori == 'A')
        {
            anim4.rectSourceSprite.top = anim4.tamSprite_y;
        }
    }
    else
    {
        if (Ori == 'D')
        {
            anim.rectSourceSprite.top = anim.tamSprite_y * 0;
        }
        else if (Ori == 'A')
        {
            anim.rectSourceSprite.top = anim.tamSprite_y;
        }
    }
}

void Player::attack_2(sf::RenderWindow& app)
{
    if (life > 0)
    {
        if (isFire && timeFire.getElapsedTime().asSeconds() > 0.5)
        {
            s1.setVolume(15);
            s1.play();
            Bullet* bala1 = new Bullet(anim7, 6.5);
            bala1->setScale(2.f, 2.f);

            if (Ori == 'A')
            {
                bala1->setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y);
                bala1->orientacion(false, true);
            }
            else
            {
                bala1->setPosition(anim.sp.getPosition().x, anim.sp.getPosition().y);
                bala1->orientacion(true);
            }

            balas.push_back(bala1);
            timeFire.restart();
        }
    }
}

void Player::draw_1(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim.sp.setScale(tam_x, tam_y);
        anim2.sp.setScale(tam_x, tam_y);
        anim3.sp.setScale(tam_x, tam_y);
        anim4.sp.setScale(tam_x, tam_y);
        anim5.sp.setScale(tam_x, tam_y);
        anim6.sp.setScale(tam_x, tam_y);
        orientacion_p1();
        move_p1();
        isFire = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            anim3.Draw(app);
            anim3.Update_Una_Vez();
            if (wait_Jump.getElapsedTime().asSeconds() > 0.1)
            {
                anim3.Reset();
                wait_Jump.restart();
            }         
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            anim2.Draw(app);
            anim2.Update();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
        {
            anim4.Draw(app);
            anim4.Update();
            isFire = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        {
            anim5.Draw(app);
            anim5.Update_Una_Vez();
            if (wait_Jump.getElapsedTime().asSeconds() > 0.1)
            {
                anim3.Reset();
                wait_Jump.restart();
            }
        }
        else
        {
            if (Ori == 'A')
                anim.rectSourceSprite.top = anim.tamSprite_y;
            else if (Ori == 'D')
                anim.rectSourceSprite.top = anim.tamSprite_y * 0;
            anim.Draw(app);
            anim.Update();       
        }
    }
    else
    {
        anim.sp.move(0.f, 9.8f);
        anim6.Update_Una_Vez();
        anim6.Draw(app);
    }
}

void Player::draw_2(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim.sp.setScale(tam_x, tam_y);
        anim2.sp.setScale(tam_x, tam_y);
        anim3.sp.setScale(tam_x, tam_y);
        anim4.sp.setScale(tam_x, tam_y);
        anim5.sp.setScale(tam_x, tam_y);
        anim6.sp.setScale(tam_x, tam_y);
        orientacion_p2();
        move_p2();
        isFire = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            anim3.Draw(app);
            anim3.Update();
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            anim2.Draw(app);
            anim2.Update();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl))
        {
            anim4.Draw(app);
            anim4.Update();
            isFire = true;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
        {
            anim5.Draw(app);
            anim5.Update();
        }
        else
        {
            if (Ori == 'A')
                anim.rectSourceSprite.top = anim.tamSprite_y;
            else if (Ori == 'D')
                anim.rectSourceSprite.top = anim.tamSprite_y * 0;
            anim.Draw(app);
            anim.Update();
        }
    }
    else
    {
        anim.sp.move(0.f, 9.8f);
        anim6.Update_Una_Vez();
        anim6.Draw(app);
    }
}

void Player::colision_platform(Platform& pl1)
{
    if (pl1.lock)
    {
        c1.colision_platform_player(anim.sp, pl1.sp_p, vsx, vsy, vsx_aux);
        c1.colision_platform_player(anim2.sp, pl1.sp_p, vsx, vsy, vsx_aux);
        c1.colision_platform_player(anim3.sp, pl1.sp_p, vsx, vsy, vsx_aux);
        c1.colision_platform_player(anim4.sp, pl1.sp_p, vsx, vsy, vsx_aux);
        c1.colision_platform_player(anim5.sp, pl1.sp_p, vsx, vsy, vsx_aux);
        c1.colision_platform_player(anim6.sp, pl1.sp_p, vsx, vsy, vsx_aux);
    }
}

void Player::colision_windows(int width, int height)
{
    c1.colision_pantalla_player(anim.sp, width, height);
}

void Player::colision_enemy(Enemy& e1)
{
    if (life > 0)
    {
        if (e1.life > 0)
        {
            if (c1.colision_entity_entity(anim.sp, e1.anim.sp))
            {  
                s2.play();
                puntaje.muertes++;
                life--;
                resucitar = true;
                time_dead.restart();
            }
            for (auto& b : e1.balas)
            {
                if (c1.colision_entity_entity(anim.sp, b->anim.sp))
                {
                    s2.play();
                    puntaje.muertes++;
                    life--;
                    resucitar = true;
                    time_dead.restart();
                }
            }
        }
    }
}

void Player::resusitar(float pos_x, float pos_y)
{
    if (resucitar && time_dead.getElapsedTime().asSeconds() > 8.0)
    {
        s3.play();
        anim.sp.setPosition(pos_x, pos_y);
        anim6.Reset();
        life = 1;
        resucitar = false;
        time_dead.restart();
    }
}

