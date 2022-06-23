#include "Player.h"

Player::Player()
{
    Ori = true;
}

Player::~Player()
{

}

void Player::move_p1() //Player 1
{
    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        anim.sp.move(0.f, -vsy);
    */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        anim.sp.move(-vsx, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        anim.sp.move(vsx, 0.f);
}

void Player::orientacion_p1() //Player 1
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))   //Salto
        anim.rectSourceSprite.top = anim.tamSprite_y;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))   //Izquierda
    {
        anim.rectSourceSprite.top = anim.tamSprite_y;
        Ori = 'A';
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))  //Derecha
    {
        anim.rectSourceSprite.top = anim.tamSprite_y * 0;
        Ori = 'D';
    }
}

void Player::move_p2() //Player 2
{
    /*
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        anim.sp.move(0.f, -vsy);
    */
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        anim.sp.move(-vsx, 0.f);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        anim.sp.move(vsx, 0.f);
}

void Player::orientacion_p2() //Player 2
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))   //Salto
        anim.rectSourceSprite.top = anim.tamSprite_y;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))   //Izquierda
    {
        anim.rectSourceSprite.top = anim.tamSprite_y;
        Ori = 'L';
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))  //Derecha
    {
        anim.rectSourceSprite.top = anim.tamSprite_y * 0;
        Ori = 'R';
    }
}

void Player::Update2(sf::RenderWindow& app, bool p)
{
    if (p == true)
    {
        orientacion_p1();
        move_p1();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
            Update();

        else
        {
            if (Ori == 'A')
                anim.rectSourceSprite.top = anim.tamSprite_y;
            else
                anim.rectSourceSprite.top = anim.tamSprite_y * 0;

            anim.rectSourceSprite.left = 0;
            anim.sp.setTextureRect(anim.rectSourceSprite);
        }
    }
    else
    {
        orientacion_p2();
        move_p2();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            Update();

        else
        {
            if (Ori == 'L')
                anim.rectSourceSprite.top = anim.tamSprite_y;
            else
                anim.rectSourceSprite.top = anim.tamSprite_y * 0;
            anim.rectSourceSprite.left = 0;
            anim.sp.setTextureRect(anim.rectSourceSprite);
        }
    }
    Draw(app);
}

