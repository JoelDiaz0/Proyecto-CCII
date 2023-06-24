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

void Animation::Initialize(sf::Texture& t1,const int& tamSprite_x, const int& tamSprite_y, const int& num_Sprites, const double& moveSpeed)
{
    sp.setTexture(t1);
    this->tamSprite_x = tamSprite_x;
    this->tamSprite_y = tamSprite_y;
    this->moveSpeed = moveSpeed;
    this->num_Sprites = num_Sprites;
    rectSourceSprite.width = tamSprite_x;
    rectSourceSprite.height = tamSprite_y;
    rectSourceSprite.top = 0;
    rectSourceSprite.left = 0;
    sp.setTextureRect(rectSourceSprite);
}

void Animation::Update()
{
    if (time_anim.getElapsedTime().asSeconds() > moveSpeed)
    {
        if (rectSourceSprite.left == tamSprite_x * (num_Sprites - 1))
            rectSourceSprite.left = 0;
        else
            rectSourceSprite.left += tamSprite_x;
        sp.setTextureRect(rectSourceSprite);
        time_anim.restart();
    }
}

void Animation::Update_Una_Vez()
{
    if (time_anim.getElapsedTime().asSeconds() > moveSpeed)
    {
        if (rectSourceSprite.left < tamSprite_x * (num_Sprites - 1))
            rectSourceSprite.left += tamSprite_x;
        else
            rectSourceSprite.left = tamSprite_x * (num_Sprites - 1);         
        sp.setTextureRect(rectSourceSprite);
        time_anim.restart();
    }
}

void Animation::Reset()
{
    rectSourceSprite.left = 0;
}

void Animation::Draw(sf::RenderWindow& app)
{
    app.draw(sp);
}

