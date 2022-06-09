#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include <iostream>
using namespace std;

const int W = 1280;
const int H = 720;

int main()
{
    //CREAR VENTANA
    sf::RenderWindow App(sf::VideoMode(W, H, 32), "Juego"); 
    bool fullscream = false;

    //FUNCIONES PARA ANIMACION
    enum Direction { Down, Left, Right, Up };
    sf::Vector2i source;
    source.x = 1;
    source.y = Down;

    //CARGAR ARCHIVOS
    sf::Music m1;
    m1.openFromFile("data\\music\\music1.ogg");
    m1.setVolume(10);
    m1.play();

    sf::Texture t1, t2, t3;
    t1.loadFromFile("data\\sprites\\Enemigo2.png");
    t2.loadFromFile("data\\sprites\\Enemigo1A.png");
    t3.loadFromFile("data\\sprites\\fondo.jpg");

    sf::Sprite Ene1, Ene2, background;
    Ene1.setTexture(t1);
    Ene1.setPosition(W / 2, H / 2);

    Ene2.setTexture(t2);
    Ene2.setPosition(W / 2, H / 2);

    background.setTexture(t3);

    Animation anim1(t1);
    Player jugador;

    cout << "125" << endl;

    //FUNCION PRINCIPAL
    while (App.isOpen())
    {
        App.setFramerateLimit(15);
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
                jugador.update(ev);
                anim1.config(ev);

            default:
                break;
            }
        }

        //LOGICA DE MOSTRAR ENTIDADES
        source.x++;
        if (source.x * 48 >= t2.getSize().x)
            source.x = 0;

        Ene2.setTextureRect(sf::IntRect(source.x * 48, source.y * 72, 48, 72));
        App.draw(Ene2);
    
        //MOSTRAR JUGADOR CON CLASES
        anim1.update2(51, t1.getSize().x, 51, 70.7, 51, 70.7, 0, true);
        jugador.settings(anim1, W / 2, H / 2);
        jugador.draw(App);

        App.display();
        App.clear();
        App.draw(background);
    }

    return EXIT_SUCCESS;
}