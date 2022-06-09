#include "Animation.h"

Animation::Animation()
{
    moveSpeed = 0;
    tamSprite_x = 0;
    tamSprite_y = 0,
    posx = 0;
    posy = 0;
}

Animation::~Animation()
{
}

void Animation::Initialize(sf::Texture& t1, int tamSprite_x, int tamSprite_y, double moveSpeed)
{
    sp.setTexture(t1);
    this->tamSprite_x = tamSprite_x;
    this->tamSprite_y = tamSprite_y;
    this->moveSpeed = moveSpeed;

    rectSourceSprite.width = tamSprite_x;
    rectSourceSprite.height = tamSprite_y;
    rectSourceSprite.top = 0;
    rectSourceSprite.left = 0;

    sp.setTextureRect(rectSourceSprite);
}

void Animation::orientation(sf::Event& ev)
{
    if (ev.type == sf::Event::KeyPressed)
    {
        if (ev.key.code == sf::Keyboard::Up)
            rectSourceSprite.top = tamSprite_y * 3;
        else if (ev.key.code == sf::Keyboard::Down)
            rectSourceSprite.top = tamSprite_y * 0;
        else if (ev.key.code == sf::Keyboard::Left)
            rectSourceSprite.top = tamSprite_y;
        else if (ev.key.code == sf::Keyboard::Right)
            rectSourceSprite.top = tamSprite_y * 2;
    }
}

void Animation::Update()
{
    if (time.getElapsedTime().asSeconds() > moveSpeed)
    {
        if (rectSourceSprite.left == tamSprite_x * 2)
            rectSourceSprite.left = 0;
        else
            rectSourceSprite.left += tamSprite_x;
        sp.setTextureRect(rectSourceSprite);
        time.restart();
    }
}

void Animation::Draw(sf::RenderWindow& app)
{
    sp.setPosition(posx, posy);
    app.draw(sp);
}