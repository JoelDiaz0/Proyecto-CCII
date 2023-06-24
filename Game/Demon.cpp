#include "Demon.h"

Demon::Demon() : Enemy()
{
    tipo_enemigo = TIPO_ENEMIGO::DEMON;
    life = 100;
}

Demon::~Demon()
{
}

sf::Texture Demon::tex_enemy_1;
sf::Texture Demon::tex_enemy_2;

void Demon::initialize(float pos_x, float pos_y, float vsx, float vsy)
{
    tex_enemy_1.loadFromFile("data\\sprites\\demon_walk.png");
    tex_enemy_2.loadFromFile("data\\sprites\\demon_attack.png");
    anim_1.Initialize(tex_enemy_1, 80, 109, 3, 0.2);
    anim_2.Initialize(tex_enemy_2, 122, 112, 2, 0.075);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
    sb1.loadFromFile("data\\sound\\bala_1.ogg");
    s1.setBuffer(sb1);
    s1.setVolume(80.f);
}

int Demon::get_puntaje_enemigo()
{
    return 500;
}

Enemy::TIPO_ENEMIGO Demon::get_tipo_enemigo()
{
    return tipo_enemigo;
}

void Demon::attack(sf::RenderWindow& app)
{
    if (life > 0)
    {
        if (time_attack.getElapsedTime().asSeconds() > 7.5)
        {
            isFire = true;
            time_attack.restart();
        }
        if (isFire)
        {
            float extra_vs{ 1.0f };
            for (int i = 1; i < 4; i++)
            {
                s1.play();
                s1.setLoop(true);
                Bullet* bala1 = new Bullet_Demon;
                bala1->Initialize(4.5f * extra_vs);
                bala1->setScale(1.5f, 1.5f);
                bala1->setAngle_sin(15);
                Bullet* bala2 = new Bullet_Demon();
                bala2->Initialize(4.5f * extra_vs);
                bala2->setScale(1.5f, 1.5f);
                Bullet* bala3 = new Bullet_Demon();
                bala3->Initialize(4.5f * extra_vs);
                bala3->setScale(1.5f, 1.5f);
                bala3->setAngle_sin(-15);
                if (Ori == 'A')
                {
                    anim_2.rectSourceSprite.top = anim_2.tamSprite_y;
                    bala1->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y + anim_2.tamSprite_y / 2.f);
                    bala1->orientacion(false);
                    bala2->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y + anim_2.tamSprite_y / 2.f);
                    bala2->orientacion(false);
                    bala3->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y + anim_2.tamSprite_y / 2.f);
                    bala3->orientacion(false);
                }
                else
                {
                    anim_2.rectSourceSprite.top = anim_2.tamSprite_y * 0;
                    bala1->setPosition(anim_1.sp.getPosition().x + anim_1.tamSprite_x, anim_1.sp.getPosition().y + anim_2.tamSprite_y / 2.f);
                    bala2->setPosition(anim_1.sp.getPosition().x + anim_1.tamSprite_x, anim_1.sp.getPosition().y + anim_2.tamSprite_y / 2.f);
                    bala3->setPosition(anim_1.sp.getPosition().x + anim_1.tamSprite_x, anim_1.sp.getPosition().y + anim_2.tamSprite_y / 2.f);
                }
                balas.push_back(bala1);
                balas.push_back(bala2);
                balas.push_back(bala3);
                extra_vs += 0.2f;
            }
            reload = true;
            isFire = false;
            stop = true;
            wait_attack.restart();
        }

        if (reload && wait_attack.getElapsedTime().asSeconds() > 1.5)
        {
            if (Ori == 'A')
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y;
            else
                anim_1.rectSourceSprite.top = anim_1.tamSprite_y * 0;
            reload = false;
            stop = false;
            s1.setLoop(false);
        }
    }
    else {
        s1.stop();
    }
}

void Demon::move()
{
    if (life > 0)
    {
        if (!stop)
            anim_1.sp.move(vsx, 9.8f);
    }
}

void Demon::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim_2.sp.setScale(sf::Vector2f(tam_x, tam_y));
        if (!isFire && !reload)
        {
            anim_1.Draw(app);
            anim_1.Update();
        }
        if (stop)
        {
            anim_2.Draw(app);
            anim_2.Update();
        }
    }
}

void Demon::update()
{
    anim_2.sp.setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
}