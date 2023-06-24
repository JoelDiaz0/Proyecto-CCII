#include "Buceo.h"

Buceo::Buceo() : Enemy()
{
    tipo_enemigo = TIPO_ENEMIGO::BUCEO;
    life = 5;
}

Buceo::~Buceo()
{
}

sf::Texture Buceo::tex_enemy_1;

void Buceo::initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f)
{
    tex_enemy_1.loadFromFile("data\\sprites\\buceo.png");
    anim_1.Initialize(tex_enemy_1, 29, 26, 8, 0.075);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
}

int Buceo::get_puntaje_enemigo()
{
    return 25;
}

Enemy::TIPO_ENEMIGO Buceo::get_tipo_enemigo()
{
    return tipo_enemigo;
}

void Buceo::move()
{
    if (life > 0)
    {
        if (!stop)
            anim_1.sp.move(vsx, vsy);
    }
}

void Buceo::attack(sf::RenderWindow& app)
{
}

void Buceo::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim_1.Draw(app);
    }
}

void Buceo::update()
{
    anim_1.Update();
}