#include "Harpy.h"

Harpy::Harpy() : Enemy()
{
    tipo_enemigo = TIPO_ENEMIGO::HARPY;
    life = 20;
}

Harpy::~Harpy()
{

}

sf::Texture Harpy::tex_enemy_1;

void Harpy::initialize(float pos_x, float pos_y, float vsx, float vsy)
{
    tex_enemy_1.loadFromFile("data\\sprites\\harpy.png");
    anim_1.Initialize(tex_enemy_1, 47, 77, 7, 0.09);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
}

void Harpy::update()
{
}

void Harpy::move()
{
    if (life > 0)
    {
        if (!stop)
        {
            anim_1.sp.move(vsx, vsy / 3);
            if (wait_move.getElapsedTime().asSeconds() > 1.5f)
            {
                vsy = -vsy;
                wait_move.restart();
            }
        }
    }
}

void Harpy::attack(sf::RenderWindow& app)
{
}

void Harpy::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim_1.Draw(app);
        anim_1.Update();
    }
}

int Harpy::get_puntaje_enemigo()
{
    return 75;
}

Enemy::TIPO_ENEMIGO Harpy::get_tipo_enemigo()
{
    return tipo_enemigo;
}
