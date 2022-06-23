#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Colision.h"
#include <iostream>
using std::cout;
using std::endl;

const int W = 1280;
const int H = 720;

int main()
{
    sf::RenderWindow App(sf::VideoMode(W, H, 32), "Juego");
    App.setFramerateLimit(60);
    bool fullscream = false;

    //CARGAR ARCHIVOS
    sf::Music m1;
    m1.openFromFile("data\\music\\music1.ogg");
    m1.setVolume(5);
    m1.play();

    sf::Texture t1, t2, t3, t4;
    t1.loadFromFile("data\\sprites\\p1.png");
    t2.loadFromFile("data\\sprites\\p2.png");
    t3.loadFromFile("data\\sprites\\fondo.jpg");
    t4.loadFromFile("data\\sprites\\nature-paltformer.png");

    sf::Sprite background;
    background.setTexture(t3);

    Animation anim1, anim2;
    anim1.Initialize(t1, 24, 32, 3, 0.075);
    anim2.Initialize(t2, 18, 24, 3, 0.075);

    Player p1, p2;
    p1.Initialize(anim1, W / 2, H / 2, 3);
    p1.Scale(3, 3);
    p2.Initialize(anim2, W / 2, H / 2 + 15, 3.5);
    p2.Scale(3.5, 3.5);

    Platform pl1(t4);
    pl1.generar_tierra();
    pl1.scale_platform(2, 2);

    Colision c1, c2;

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
                    App.setFramerateLimit(60);
                    fullscream = true;
                }
                else if (ev.key.code == sf::Keyboard::Escape && fullscream == true)
                {
                    App.create(sf::VideoMode(W, H, 32), "Juego");
                    App.setFramerateLimit(60);
                    fullscream = false;
                }
            default:
                break;
            }
        }

        App.clear();
        App.draw(background);

        c1.colision_pantalla(p1);
        c2.colision_pantalla(p2);

        p1.Update2(App, true);
        p2.Update2(App, false);

        pl1.draw(App);
        App.display();
    }

    return EXIT_SUCCESS;
}