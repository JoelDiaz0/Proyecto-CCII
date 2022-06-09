#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::setControl(sf::Event& ev)
{
    anim.orientation(ev);

    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::Up)
            anim.posy -= vsy;
        else if (ev.key.code == sf::Keyboard::Down)
            anim.posy += vsy;
        else if (ev.key.code == sf::Keyboard::Left)
            anim.posx -= vsx;
        else if (ev.key.code == sf::Keyboard::Right)
            anim.posx += vsx;
    }
}

void Player::Update()
{

}


