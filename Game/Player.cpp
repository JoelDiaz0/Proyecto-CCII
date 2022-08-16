#include "Player.h"

Player::Player()
{
    waitJump = false;
    jump = false;
    isFire = false;
    stop = false;
    resucitar = false;
    life = 1;
    Ori = 'D';
    vsx_aux = 0.f;
    vsx = 0.f;
    vsy = 0.f;
    tam_x = 1.f;
    tam_y = 1.f;
    sb0_1.loadFromFile("data\\sound\\dead.ogg"); //Sonido de muerte
    s0_1.setBuffer(sb0_1);
    s0_1.setVolume(90.f);
    sb0_2.loadFromFile("data\\sound\\revivir.ogg"); //Sonido de revivir
    s0_2.setBuffer(sb0_2);
    s0_2.setVolume(25.f);
}

Player::~Player()
{
}


void Player::colision_platform(Platform& pl1)
{
    if (pl1.lock)
    {
        c1.colision_platform_player(anim_1.sp, pl1.sp_p, vsx, vsy, vsx_aux);
    }
}

void Player::colision_windows(int width, int height)
{
    c1.colision_pantalla_player(anim_1.sp, width, height);
}

void Player::draw_bullets(sf::RenderWindow& app)
{
    if (!balas.empty())
    {
        for (auto& b : balas)
        {
            if (!b->impact)
            {
                b->draw(app);
                b->update();
                b->move();
            }
        }
    }
}

void Player::colision_bullets(Platform& plt, int width, int height)
{
    if (!balas.empty())
    {
        for (auto& b : balas)
        {
            if (!b->impact)
            {
                b->colision_window(width, height);
                b->colision_platform(plt);
            }
               
        }
    }
}

void Player::colision_enemy(Enemy& e1)
{
    if (life > 0)
    {
        if (e1.life > 0)
        {
            if (c1.colision_entity_entity(anim_1.sp, e1.anim_1.sp))
            {
                s0_1.play();
                puntaje.muertes++;
                life--;
                resucitar = true;
                time_dead.restart();
            }
            for (auto& b : e1.balas)
            {
                if (c1.colision_entity_entity(anim_1.sp, b->anim.sp) && !b->impact)
                {
                    s0_1.play();
                    puntaje.muertes++;
                    life--;
                    b->impact = true;
                    resucitar = true;
                    time_dead.restart();
                }
            }
        }
    }
}

void Player::setScale(float tam_x, float tam_y)
{
    this->tam_x = tam_x;
    this->tam_y = tam_y;
}

void Player::setPosition(float pos_x, float pos_y)
{
    anim_1.sp.setPosition(pos_x, pos_y);
}

float Player::getPosition_x()
{
    return anim_1.sp.getPosition().x;
}

float Player::getPosition_y()
{
    return anim_1.sp.getPosition().y;
}

char Player::getOrientacion()
{
    return Ori;
}