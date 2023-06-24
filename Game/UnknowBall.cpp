#include "UnknowBall.h"

UnknowBall::UnknowBall() : Enemy()
{
    tipo_enemigo = TIPO_ENEMIGO::UNKNOW_BALL;
    life = 50;
}

UnknowBall::~UnknowBall()
{
}

sf::Texture UnknowBall::tex_enemy_1;

void UnknowBall::initialize(float pos_x, float pos_y, float vsx, float vsy = 0.f)
{
    tex_enemy_1.loadFromFile("data\\sprites\\unknow_ball.png");
    anim_1.Initialize(tex_enemy_1, 24, 23, 3, 0.2);
    this->vsx = vsx;
    this->vsy = vsy;
    anim_1.sp.setPosition(pos_x, pos_y);
    sb1.loadFromFile("data\\sound\\bala_1.ogg");
    s1.setBuffer(sb1);
    s1.setVolume(150.f);
}

int UnknowBall::get_puntaje_enemigo()
{
    return 100;
}

Enemy::TIPO_ENEMIGO UnknowBall::get_tipo_enemigo()
{
    return tipo_enemigo;
}

void UnknowBall::move()
{
    if (life > 0)
    {
        if (!stop)
            anim_1.sp.move(vsx, vsy);
    }
}

void UnknowBall::attack(sf::RenderWindow& app)
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
            balas.push_back(bala);
            balas.push_back(bala2);
            balas.push_back(bala3);
            balas.push_back(bala4);
            isFire = false;
        }
    }
}

void UnknowBall::Draw(sf::RenderWindow& app)
{
    if (life > 0)
    {
        anim_1.sp.setScale(sf::Vector2f(tam_x, tam_y));
        anim_1.Draw(app);
    }
}

void UnknowBall::update()
{
    anim_1.Update();
}
