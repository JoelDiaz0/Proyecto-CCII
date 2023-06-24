#include "Ovni.h"

Ovni::Ovni() : Enemy()
{
    tipo_enemigo = TIPO_ENEMIGO::OVNI;
    life = 30;
}

Ovni::~Ovni()
{

}

sf::Texture Ovni::tex_enemy_1;

void Ovni::initialize(float pos_x, float pos_y, float vsx, float vsy)
{
    tex_enemy_1.loadFromFile("data\\sprites\\ovni.png");
    anim_1.Initialize(tex_enemy_1, 16, 16, 4, 0.09);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
}

void Ovni::update()
{
}

void Ovni::move()
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

void Ovni::attack(sf::RenderWindow& app)
{
}

void Ovni::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim_1.Draw(app);
        anim_1.Update();
    }
}

int Ovni::get_puntaje_enemigo()
{
    return 50;
}

Enemy::TIPO_ENEMIGO Ovni::get_tipo_enemigo()
{
    return tipo_enemigo;
}
