#include "Throwingfire.h"

Throwingfire::Throwingfire() : Enemy()
{
    tipo_enemigo = TIPO_ENEMIGO::THROWING_FIRE;
    life = 100;
}

Throwingfire::~Throwingfire()
{
}

sf::Texture Throwingfire::tex_enemy_1;

void Throwingfire::initialize(float pos_x, float pos_y, float vsx, float vsy)
{
    tex_enemy_1.loadFromFile("data\\sprites\\throwingfire.png");
    anim_1.Initialize(tex_enemy_1, 39, 46, 1, 0.055);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
    sb1.loadFromFile("data\\sound\\FlameAtack.ogg");
    s1.setBuffer(sb1);
    s1.setVolume(40.f);
}

int Throwingfire::get_puntaje_enemigo()
{
    return 200;
}

Enemy::TIPO_ENEMIGO Throwingfire::get_tipo_enemigo()
{
    return tipo_enemigo;
}

void Throwingfire::move()
{
    if (life > 0)
    {
        if (!stop)
        {
            anim_1.sp.move(vsx, vsy / 3.f);

            if (wait_move.getElapsedTime().asSeconds() > 0.5)
            {
                vsy = -vsy;
                wait_move.restart();
            }
        }
    }
}

void Throwingfire::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        if (!isFire && !reload)
        {
            if (Ori == 'A')
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y;
            else
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y * 0;
        }
        if (stop)
        {
            if (Ori == 'A')
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y * 3;
            else
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y * 2;
        }
        anim_1.Draw(app);
        anim_1.Update();
    }
}

void Throwingfire::update()
{
}

void Throwingfire::attack(sf::RenderWindow& app)
{
    if (life > 0)
    {
        if (time_attack.getElapsedTime().asSeconds() > 7.0)
        {
            isFire = true;
            time_attack.restart();
        }

        if (isFire)
        {
            s1.setVolume(25.f);
            s1.play();

            Bullet* bala1 = new Bullet_Fire2();
            bala1->Initialize(7.5f);
            bala1->setScale(3.f, 3.f);

            if (Ori == 'A')
            {
                bala1->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y + anim_1.tamSprite_y / 2);
                bala1->orientacion(false);
            }
            else
            {
                bala1->setPosition(anim_1.sp.getPosition().x + anim_1.tamSprite_x, anim_1.sp.getPosition().y + anim_1.tamSprite_y / 2);
            }
            balas.push_back(bala1);
            reload = true;
            isFire = false;
            stop = true;
            wait_attack.restart();
        }

        if (reload && wait_attack.getElapsedTime().asSeconds() > 1.5)
        {
            reload = false;
            stop = false;
        }
    }
}