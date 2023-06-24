#include "Alien.h"

Alien::Alien() : Enemy()
{
    tipo_enemigo = TIPO_ENEMIGO::ALIEN;
    life = 50;
}

Alien::~Alien()
{
}

sf::Texture Alien::tex_enemy_1;

void Alien::initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f)
{
    tex_enemy_1.loadFromFile("data\\sprites\\alien.png");
    anim_1.Initialize(tex_enemy_1, 156, 139, 4, 0.1);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
}

int Alien::get_puntaje_enemigo()
{
    return 50;
}

Enemy::TIPO_ENEMIGO Alien::get_tipo_enemigo()
{
    return tipo_enemigo;
}

void Alien::move()
{
    if (life > 0)
    {
        if (!stop)
            anim_1.sp.move(vsx, 9.8f);
    }
}

void Alien::attack(sf::RenderWindow& app)
{
}

void Alien::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim_1.Draw(app);
    }
}

void Alien::update()
{
    anim_1.Update();
}


