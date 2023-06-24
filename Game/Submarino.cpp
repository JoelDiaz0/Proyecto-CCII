#include "Submarino.h"

Submarino::Submarino() : Enemy()
{
    tipo_enemigo = TIPO_ENEMIGO::SUBMARINO;
    life = 50;
}

Submarino::~Submarino()
{
}

sf::Texture Submarino::tex_enemy_1;

void Submarino::initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f)
{
    tex_enemy_1.loadFromFile("data\\sprites\\submarino.png");
    anim_1.Initialize(tex_enemy_1, 31, 26, 4, 0.1);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
    sb1.loadFromFile("data\\sound\\bala_1.ogg");
    s1.setBuffer(sb1);
    s1.setVolume(150.f);
}

int Submarino::get_puntaje_enemigo()
{
    return 90;
}

Enemy::TIPO_ENEMIGO Submarino::get_tipo_enemigo()
{
    return tipo_enemigo;
}

void Submarino::move()
{
    if (life > 0)
    {
        if (!stop)
            anim_1.sp.move(vsx, vsy);
    }
}

void Submarino::attack(sf::RenderWindow& app)
{
    if (life > 0) {

        if (time_attack.getElapsedTime().asSeconds() > 10.f) {
            isFire = true;
            time_attack.restart();
        }

        if (isFire) {
            s1.play();   
            Bullet* bala = new Bullet();
            bala->Initialize(4.5f);
            bala->setPosition(anim_1.sp.getPosition().x + anim_1.sp.getTextureRect().width, anim_1.sp.getPosition().y);
            bala->setScale(2.5f, 2.5f);
            Bullet* bala2 = new Bullet();
            bala2->Initialize(-4.5f);
            bala2->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
            bala2->setScale(2.5f, 2.5f);
            Bullet* bala3 = new Bullet();
            bala3->Initialize(0.f, 4.5f);
            bala3->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y + anim_1.sp.getTextureRect().height);
            bala3->setScale(2.5f, 2.5f);
            Bullet* bala4 = new Bullet();
            bala4->Initialize(0.f, -4.5f);
            bala4->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
            bala4->setScale(2.5f, 2.5f);   
            Bullet* bala5 = new Bullet();
            bala5->Initialize(4.5f, -4.5f);
            bala5->setPosition(anim_1.sp.getPosition().x + anim_1.sp.getTextureRect().width, anim_1.sp.getPosition().y);
            bala5->setScale(2.5f, 2.5f);
            Bullet* bala6 = new Bullet();
            bala6->Initialize(-4.5f, -4.5f);
            bala6->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
            bala6->setScale(2.5f, 2.5f);
            Bullet* bala7 = new Bullet();
            bala7->Initialize(-4.5f, 4.5f);
            bala7->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y + anim_1.sp.getTextureRect().height);
            bala7->setScale(2.5f, 2.5f);
            Bullet* bala8 = new Bullet();
            bala8->Initialize(4.5f, 4.5f);
            bala8->setPosition(anim_1.sp.getPosition().x, anim_1.sp.getPosition().y);
            bala8->setScale(2.5f, 2.5f);

            balas.push_back(bala);
            balas.push_back(bala2);
            balas.push_back(bala3);
            balas.push_back(bala4);
            balas.push_back(bala5);
            balas.push_back(bala6);
            balas.push_back(bala7);
            balas.push_back(bala8);
            isFire = false;
        }
    }
}

void Submarino::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim_1.Draw(app);
    }
}

void Submarino::update()
{
    anim_1.Update();
}