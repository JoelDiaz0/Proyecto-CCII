#include "Oruga.h"

Oruga::Oruga() : Enemy()
{
    tipo_enemigo = TIPO_ENEMIGO::ORUGA;
    life = 50;
}

Oruga::~Oruga()
{
}

sf::Texture Oruga::tex_enemy_1;

void Oruga::initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f)
{
    tex_enemy_1.loadFromFile("data\\sprites\\oruga.png");
    anim_1.Initialize(tex_enemy_1, 32, 19, 3, 0.1);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
}

int Oruga::get_puntaje_enemigo()
{
    return 50;
}

Enemy::TIPO_ENEMIGO Oruga::get_tipo_enemigo()
{
    return tipo_enemigo;
}

void Oruga::move()
{
    if (life > 0)
    {
        if (!stop)
            anim_1.sp.move(vsx, 9.8f);
    }
}

void Oruga::attack(sf::RenderWindow& app)
{
}

void Oruga::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim_1.Draw(app);
    }
}

void Oruga::update()
{
    anim_1.Update();
}
