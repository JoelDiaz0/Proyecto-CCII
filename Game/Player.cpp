#include "Player.h"

Player::Player() : Entity()
{
    waitJump = false;
    jump = false;
    isFire = false;
    stop = false;
}

Player::~Player()
{
    for (auto b : balas)
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
            anim.sp.move(-3.5 * 2.f, -vsy * 4.5);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            anim.sp.move(3.5 * 2.f, -vsy * 4.5);
        }
        else
        {
            anim.sp.move(0.f, -vsy * 4.5);
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
        anim.sp.move(0.f, vsy * 1.5);
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
    if (isFire && timeFire.getElapsedTime().asSeconds() > 1.0)
    {
        s1.setVolume(15);
        s1.play();
        Bullet* bala1 = new Bullet(anim7, 7.5);
        bala1->scale(2.5, 2.5);

        if (Ori == 'A')
        {
            bala1->position(anim.sp.getPosition().x, anim.sp.getPosition().y);
            bala1->orientacion(false);
        }
        else
            bala1->position(anim.sp.getPosition().x, anim.sp.getPosition().y);
        balas.push_back(bala1);
        timeFire.restart();
    }

    if (!balas.empty())
    {
        for (auto b : balas)
        {
            b->fire_1();
            b->draw(app);
            b->update();
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
            anim.sp.move(-3.5 * 2.f, -vsy * 4.5);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            anim.sp.move(3.5 * 2.f, -vsy * 4.5);
        }
        else
        {
            anim.sp.move(0.f, -vsy * 4.5);
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
        anim.sp.move(0.f, vsy * 1.5);
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
    if (isFire && timeFire.getElapsedTime().asSeconds() > 0.7)
    {
        s1.setVolume(15);
        s1.play();
        Bullet* bala1 = new Bullet(anim7, 6.5);
        bala1->scale(2.f, 2.f);

        if (Ori == 'A')
        {
            bala1->position(anim.sp.getPosition().x, anim.sp.getPosition().y);
            bala1->orientacion(false, true);
        }
        else
        {
            bala1->position(anim.sp.getPosition().x, anim.sp.getPosition().y);
            bala1->orientacion(true);
        }

        balas.push_back(bala1);
        timeFire.restart();
    }

    if (!balas.empty())
    {
        for (auto b : balas)
        {
            b->fire_1();
            b->draw(app);
            b->update();
        }
    }
}

void Player::draw_1(sf::RenderWindow& app)
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
        anim3.Update();
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

void Player::draw_2(sf::RenderWindow& app)
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

void Player::colision_platform(Platform& pl1)
{
    c1.colision_platform_player(anim.sp, pl1.sp_p, vsx, vsy, vsx);
    c1.colision_platform_player(anim2.sp, pl1.sp_p, vsx, vsy, vsx);
    c1.colision_platform_player(anim3.sp, pl1.sp_p, vsx, vsy, vsx);
    c1.colision_platform_player(anim4.sp, pl1.sp_p, vsx, vsy, vsx);
    c1.colision_platform_player(anim5.sp, pl1.sp_p, vsx, vsy, vsx);
    c1.colision_platform_player(anim6.sp, pl1.sp_p, vsx, vsy, vsx);
}

void Player::colision_windows(int width, int height)
{
    c1.colision_pantalla_player(anim.sp, width, height);
}