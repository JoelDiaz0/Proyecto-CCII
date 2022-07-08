#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Demon.h"
#include "Throwingfire.h"
#include "Fungus.h"
#include "BloodMonster.h"

#include "Hell.h"
#include "Tatooine.h"
#include "montana.h"

#include <vector>
#include <iostream>
using std::cout;
using std::endl;

const int W = 1280;
const int H = 720;


int level = 5; //CAMBIO DE NIVEL


bool cargando = true;

int main()
{
    sf::RenderWindow App(sf::VideoMode(W, H, 32), "Juego");
    App.setFramerateLimit(60);
    bool fullscream = false;
    //Musica - Level 1 -----------------------------------------------
    sf::Music m1;
    m1.openFromFile("data\\music\\music1.ogg");
    m1.setVolume(6);

    //Musica - Level 5
    sf::Music m5;
    m5.openFromFile("data\\music\\the_hell.ogg");
    m5.setVolume(5.5);
    //Fondo level 1 ----------------------------------------------------------
    sf::Texture f1;
    f1.loadFromFile("data\\background\\tatooine_background.jpg");

    //Cargando texturas y creando animaciones para las BALAS
    sf::Texture txd_bala, txd_bala2, txd_bala3, txd_bala4;
    txd_bala.loadFromFile("data\\sprites\\buller_thunder.png");
    txd_bala2.loadFromFile("data\\sprites\\buller_fire_1.png");
    txd_bala3.loadFromFile("data\\sprites\\buller_fire_2.png");
    txd_bala4.loadFromFile("data\\sprites\\bala_2.png");

    Animation b1, b2, b3, b4;
    b1.Initialize(txd_bala, 34, 27, 7, 0.075);
    b2.Initialize(txd_bala2, 18, 30, 3, 0.075);
    b3.Initialize(txd_bala3, 18, 32, 3, 0.055);
    b4.Initialize(txd_bala4, 15, 15, 4, 0.075);

    //Cargando SONIDOS
    sf::SoundBuffer at, at2, at3, at4, at5;
    at.loadFromFile("data\\sound\\attack_thunder.ogg");
    at2.loadFromFile("data\\sound\\attack_fire_1.ogg");
    at3.loadFromFile("data\\sound\\damage.ogg");
    at4.loadFromFile("data\\sound\\FlameAtack.ogg");
    at5.loadFromFile("data\\sound\\bala_1.ogg");

    //Cargando texturas y creando animaciones para JUGADOR 1 y 2
    sf::Texture t1_idle, t1_run, t1_attack, t1_up, t1_jump, t1_death, t2_idle, t2_run, t2_attack, t2_up, t2_jump, t2_death;
    t1_idle.loadFromFile("data\\sprites\\p1_idle.png");
    t1_run.loadFromFile("data\\sprites\\p1_run.png");
    t1_attack.loadFromFile("data\\sprites\\p1_attack.png");
    t1_up.loadFromFile("data\\sprites\\p1_up.png");
    t1_jump.loadFromFile("data\\sprites\\p1_jump.png");
    t1_death.loadFromFile("data\\sprites\\p1_death.png");

    t2_idle.loadFromFile("data\\sprites\\p2_idle.png");
    t2_run.loadFromFile("data\\sprites\\p2_run.png");
    t2_attack.loadFromFile("data\\sprites\\p2_attack.png");
    t2_up.loadFromFile("data\\sprites\\p2_up.png");
    t2_jump.loadFromFile("data\\sprites\\p2_jump.png");
    t2_death.loadFromFile("data\\sprites\\p2_death.png");

    Animation p1_idle, p1_run, p1_attack, p1_up, p1_death, p1_jump, p2_idle, p2_run, p2_attack, p2_up, p2_death, p2_jump;
    p1_idle.Initialize(t1_idle, 21, 35, 4, 0.1);
    p1_run.Initialize(t1_run, 33, 33, 6, 0.075);
    p1_attack.Initialize(t1_attack, 34, 35, 6, 0.035);
    p1_up.Initialize(t1_up, 26, 43, 5, 0.075);
    p1_death.Initialize(t1_death, 26, 43, 5, 0.075);
    p1_jump.Initialize(t1_jump, 34, 35, 4, 0.075);

    p2_idle.Initialize(t2_idle, 20, 35, 4, 0.1);
    p2_run.Initialize(t2_run, 27, 34, 6, 0.075);
    p2_attack.Initialize(t2_attack, 28, 35, 6, 0.035);
    p2_up.Initialize(t2_up, 26, 36, 5, 0.075);
    p2_death.Initialize(t2_death, 38, 34, 6, 0.075);
    p2_jump.Initialize(t2_jump, 27, 36, 4, 0.075);

    //JUGADOR
    Player* jugador1 = new Player;
    Player* jugador2 = new Player;

    jugador1->Initialize_7(p1_idle, p1_run, p1_jump, p1_attack, p1_up, p1_death, b1, 50, H - 150, 3.5);
    jugador2->Initialize_7(p2_idle, p2_run, p2_jump, p2_attack, p2_up, p2_death, b2, 50, H - 150, 3.5);
    jugador1->Scale(2.5, 2.5);
    jugador2->Scale(2.5, 2.5);
    jugador1->cargar_audio(at);
    jugador2->cargar_audio(at2);


    //Fondo Animado
    std::vector<sf::Texture> vec_textures;
    std::vector<sf::Sprite> vec_sprites;


    ////Cargando texturas para las PLATAFORMAS
    std::vector<Platform*> vec_plataformas; //Vector de plataformas
    std::vector<Platform*> vec_plataformas3; //Vector de plataformas
    // level 1
    sf::Texture level_tatooine;
    level_tatooine.loadFromFile("data\\background\\tatooine_graphics.png");
    sf::Sprite fondo1;
    fondo1.setTexture(f1);

    //Textura level 5
    sf::Texture level_hell; 
    level_hell.loadFromFile("data\\background\\hell_graphics.png");


    //nivel montana textura
    sf::Texture text_montana;
    text_montana.loadFromFile("data\\sprites\\nivel_3\\fondo.png");
    sf::Sprite level_montana(text_montana);
   // level_montana.scale(sf::Vector2f(0.7, 0.67));



    //Cargando texturas y creando animaciones para los ENEMIGOS
    std::vector<Enemy*> vec_enemigos; //Vector de enemigos
    sf::Texture e1_a, e1_b, e2, e3, e4, e5;
    e1_a.loadFromFile("data\\sprites\\demon_walk.png");
    e1_b.loadFromFile("data\\sprites\\demon_attack.png");
    e3.loadFromFile("data\\sprites\\fungus.png");
    e4.loadFromFile("data\\sprites\\throwingfire.png");
    e5.loadFromFile("data\\sprites\\bloodmonster.png");

    Animation enemy_anim, enemy_anim2, enemy_anim3, enemy_anim4, enemy_anim5;
    enemy_anim.Initialize(e1_a, 80, 109, 3, 0.2);
    enemy_anim2.Initialize(e1_b, 122, 112, 2, 0.075);
    enemy_anim3.Initialize(e3, 17, 20, 3, 0.055);
    enemy_anim4.Initialize(e4, 39, 46, 1, 0.055);
    enemy_anim5.Initialize(e5, 75, 31, 7, 0.075);


    //static bool Coordeb{ false }; Crea el booleano para activar y desactivar el "modo debug" 
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
                }//pulsa SHIFT para imprimir en la consola las coordenadas actuales del mouse
                 //if (ev.key.code == sf::Keyboard::Key::LShift) {//Como evento, dejarlo apretado no afecta
                 //       if(Coordeb == false){
                 //               Coordeb=true;
                 //           }else{
                 //               Coordeb=false;
                 //           }
                 //} 
            default:
                break;
            }
        }

        if (level == 0)
        {
            //MENU

        }

        else if (level == 1)
        {
            if (cargando == true)
            {
                jugador1->Initialize_7(p1_idle, p1_run, p1_jump, p1_attack, p1_up, p1_death, b1, 20, 0, 3.5);
                jugador2->Initialize_7(p2_idle, p2_run, p2_jump, p2_attack, p2_up, p2_death, b2, 10, 0, 3.5);
                jugador1->Scale(2.5, 2.5);
                jugador2->Scale(2.5, 2.5);
                jugador1->cargar_audio(at);
                jugador2->cargar_audio(at2);

                cout << "Cargando una vez elementos en level " << level << endl;
                m1.play();

                double xF1{ 0.2 }, yF1{ 0.2 }; //variables para la plateforma

                Platform* piso_level1 = new Tatooine;
                piso_level1->cargar_textura(level_tatooine);
                piso_level1->generar_bloque_1();
                piso_level1->scale_platform(xF1, yF1);
                piso_level1->position(0, 220);
                vec_plataformas.push_back(piso_level1);
            }

            //DESARROLLO DEL NIVEL

            cargando = false;
            m1.setLoop(true);

            App.clear();
            App.draw(fondo1);

            jugador1->colision_windows(W, H);
            jugador2->colision_windows(W, H);

            for (auto plat : vec_plataformas)
            {
                plat->draw(App);
                jugador1->colision_platform(*plat);
                jugador2->colision_platform(*plat);
            }
            jugador1->draw_1(App);
            jugador1->Update();
            jugador1->attack_1(App);
            jugador2->draw_2(App);
            jugador2->Update();
            jugador2->attack_2(App);

            App.display();
        }

        else if (level == 2)
        {
            //KEVIN - FONDO DEL MAR
        }

        else if (level == 3)
        {
            //DIEGO - MONTAÑA
             //CARGANDO PLATAFORMAS Y ENEMIGOS
            if (cargando == true)
            {
                cout << "Cargando una vez elementos en level " << level << endl;
                m5.play();
                
               
             
            }

            //DESARROLLO DEL NIVEL
       
                cargando = false;
                m5.setLoop(true);

                App.clear();

                App.draw(level_montana);

                jugador1->colision_windows(W, H);
                jugador2->colision_windows(W, H);

                
                App.display();
        }
        
        else if (level == 4)
        {
            //AXEL - AMONGUS
        }
        
        else if (level == 5) //7/07
        {
            //CARGANDO PLATAFORMAS Y ENEMIGOS
            if (cargando == true)
            {
                cout << "Cargando una vez elementos en level " << level << endl;
                m5.play();
                for (int i = 0; i < 12; i++)
                {
                    Platform* Suelo = new Hell;
                    Suelo->cargar_textura(level_hell);
                    Suelo->generar_bloque_1();
                    Suelo->scale_platform(2.f, 2.f);
                    Suelo->position(i * 76.f * 2.f, H - 33.f);
                    vec_plataformas.push_back(Suelo);

                    Platform* Plat2 = new Hell;
                    Plat2->cargar_textura(level_hell);
                    Plat2->generar_bloque_2();
                    Plat2->scale_platform(3.f, 3.f);
                    Plat2->position(i * 64 * 2, 200);
                    vec_plataformas.push_back(Plat2);
                }
                for (int i = 0; i < 12; i++)
                {
                    if (i == 5 || i == 6)
                        continue;
                    Platform* Plat = new Hell;
                    Plat->cargar_textura(level_hell);
                    Plat->generar_bloque_2();
                    Plat->scale_platform(2.f, 2.f);
                    Plat->position(i * 64 * 2, H / 2 + 100);
                    vec_plataformas.push_back(Plat);
                }
                for (int i = 0; i < 6; i++)
                {
                    Platform* Muro = new Hell;
                    Muro->cargar_textura(level_hell);
                    Muro->generar_bloque_3();
                    Muro->scale_platform(2, 2);
                    Muro->position(0, i * 64 * 2);
                    vec_plataformas.push_back(Muro);

                    Platform* Muro2 = new Hell;
                    Muro2->cargar_textura(level_hell);
                    Muro2->generar_bloque_3();
                    Muro2->scale_platform(2, 2);
                    Muro2->position(W - 64, i * 64 * 2);
                    vec_plataformas.push_back(Muro2);
                }
                for (int i = 0; i < 1; i++)
                {
                    Enemy* enemigo1 = new Demon;
                    enemigo1->Initialize_3(enemy_anim, enemy_anim2, b4, i * 200, 0, 1.5);
                    enemigo1->Scale(1.5, 1.5);
                    enemigo1->cargar_audio(at5);

                    Enemy* enemigo4 = new BloodMonster;
                    enemigo4->Initialize(enemy_anim5, i * 250, 100, 2.f);
                    enemigo4->Scale(2.f, 2.f);

                    Enemy* enemigo2 = new Throwingfire;
                    enemigo2->Initialize_2(enemy_anim4, b3, i * 150, 250, 2.f);
                    enemigo2->Scale(3.f, 3.f);
                    enemigo2->cargar_audio(at4);

                    Enemy* enemigo3 = new Fungus;
                    enemigo3->Initialize(enemy_anim3, i * 150, 300, 3.f);
                    enemigo3->Scale(2.5, 2.5);

                    vec_enemigos.push_back(enemigo1);
                    vec_enemigos.push_back(enemigo2);
                    vec_enemigos.push_back(enemigo3);
                    vec_enemigos.push_back(enemigo4);
                }

                //Cargando fondo animado - level 5
                std::string aux;
                for (int i = 0; i < 8; i++)
                {
                    aux = "data\\background\\hell_background-" + std::to_string(i) + ".jpg";
                    sf::Texture t1;
                    t1.loadFromFile(aux);
                    vec_textures.push_back(t1);
                }
                for (int i = 0; i < 8; i++)
                {
                    sf::Sprite s1;
                    s1.setTexture(vec_textures.at(i));
                    s1.setScale(sf::Vector2f(1.75, 2.f));
                    vec_sprites.push_back(s1);
                }
            }

            //DESARROLLO DEL NIVEL
            for (auto &sp : vec_sprites)
            {
                cargando = false;
                m5.setLoop(true);

                App.clear();
                App.draw(sp);

                jugador1->colision_windows(W, H);
                jugador2->colision_windows(W, H);

                for (auto &plat : vec_plataformas)
                {
                    plat->draw(App);
                    jugador1->colision_platform(*plat);
                    jugador2->colision_platform(*plat);
                    for (auto e : vec_enemigos)
                    {
                        e->colision_platform(*plat);
                    }
                }
                for (auto &e : vec_enemigos)
                {
                    e->Draw(App);
                    e->Update();
                    e->move();
                    e->colision_windows(W, H);
                    e->attack(App);
                }
                jugador1->draw_1(App);
                jugador1->Update();
                jugador1->attack_1(App);
                jugador2->draw_2(App);
                jugador2->Update();
                jugador2->attack_2(App);

                App.display();
            }
        }

        else if (level == 6)
        {
            //ALEX
        }

        //debug
        //if (Coordeb == true) {
        //    sf::Text mousePosX, mousePosY; 
        //    sf::Font font;
        //    font.loadFromFile("data\\fonts\\Baskic8.otf"); //Fuente custom ya que quitaron el defaultfont en sfml
        //    //Este codigo podría ser usado para el SCORE
        //
        //   auto drawText = [&](sf::Text& t, std::string str, int value, int x, int y, int size, sf::Font& f, const sf::Color& c) { //Lambda porque no quería modificar otros archivos
        //        t.setString(str + std::to_string(value));        //Pone un texto y luego agrega un valor numérico convertido a texto                                                                  
        //        t.setPosition(x, y); //Posición del texto
        //        t.setCharacterSize(size); //Tamanio de caracteres
        //        t.setFont(f); //font custom
        //        t.setFillColor(c);  //Color de texto
        //        App.draw(t); //Hace aparecer el texto
        //    };
        //
        //    drawText(mousePosX, std::string("Pos X mouse: "), sf::Mouse::getPosition(App).x, 1040, 85, 30, font, sf::Color::Black);
        //    drawText(mousePosX, std::string("Pos Y mouse: "), sf::Mouse::getPosition(App).y, 1040, 125, 30, font, sf::Color::Black);
        //}      
    }

    //ELIMINAR OBJETOS Y MEMORIA
    for (auto &plt : vec_plataformas)
        delete plt;

    for (auto &e : vec_enemigos)
        delete e;

    delete jugador1, jugador2;

    return 0;
}
