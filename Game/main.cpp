#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include <iostream>

using namespace std;

const int W = 1280;
const int H = 720;

int main()
{
    sf::RenderWindow App(sf::VideoMode(W, H, 32), "Juego");
    App.setFramerateLimit(30);
    bool fullscream = false;

    //CARGAR ARCHIVOS
    sf::Music m1;
    m1.openFromFile("data\\music\\music1.ogg");
    m1.setVolume(10);
    m1.play();

    sf::Texture t1, t2, t3;
    t1.loadFromFile("data\\sprites\\Enemigo2.png");
    t3.loadFromFile("data\\sprites\\fondo.jpg");

    sf::Sprite background;
    background.setTexture(t3);

    //sf::IntRect rectSourceSprite(0, 0, 38, 64);
    //sf::Sprite sp(t1, rectSourceSprite);

    Animation anim1;
    anim1.Initialize(t1, 50, 71, 0.075);

    Player p1;
    p1.Initialize(anim1, W / 2, H / 2, 7.5);
    p1.Scale(2, 2);

    //sf::Clock clock1;

    //FUNCION PRINCIPAL
    while (App.isOpen())
    {
        sf::Event ev;
        while (App.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                App.close();
            case sf::Event::KeyPressed:
                if (ev.key.code == sf::Keyboard::Escape && fullscream == false)
                {
                    App.create(sf::VideoMode(W, H, 32), "Juego", sf::Style::Fullscreen);
                    fullscream = true;
                }
                else if (ev.key.code == sf::Keyboard::Escape && fullscream == true)
                {
                    App.create(sf::VideoMode(W, H, 32), "Juego");
                    fullscream = false;
                }

                p1.setControl(ev);

            default:
                break;
            }
        }

        //LOGICA DE GENERACION DE ANIMACION
        /*
        if (clock1.getElapsedTime().asSeconds() > 0.075)
        {
            if (rectSourceSprite.left == 76)
                rectSourceSprite.left = 0;
            else
                rectSourceSprite.left += 38;
            sp.setTextureRect(rectSourceSprite);
            clock1.restart();
        }*/

        App.clear();
        App.draw(background);

        //MOSTRAR JUGADOR CON CLASES

        p1.Draw(App);
        p1.Update();

        App.display();
    }

    return EXIT_SUCCESS;
}