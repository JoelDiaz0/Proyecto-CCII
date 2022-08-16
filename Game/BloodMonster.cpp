#include "BloodMonster.h"

BloodMonster::BloodMonster() : Enemy()
{
    nombre = "bloodmonster";
    life = 35;
}

BloodMonster::~BloodMonster()
{
}

sf::Texture BloodMonster::tex_enemy_1;

void BloodMonster::initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f)
{
    tex_enemy_1.loadFromFile("data\\sprites\\bloodmonster.png");
    anim_1.Initialize(tex_enemy_1, 75, 31, 7, 0.075);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
}

void BloodMonster::move()
{
    if (life > 0)
    {
        if (!stop)
            anim_1.sp.move(vsx, 9.8f);
    }
}

void BloodMonster::attack(sf::RenderWindow& app)
{
}

void BloodMonster::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim_1.Draw(app);
        anim_1.Update();
    }
}

void BloodMonster::update()
{
}


