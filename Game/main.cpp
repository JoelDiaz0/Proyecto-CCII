#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>
#include "menu.h"
//Enemigos
#include "Demon.h"
#include "Throwingfire.h"
#include "Fungus.h"
#include "BloodMonster.h"
#include "Harpy.h"
#include "Buceo.h"
#include "Submarino.h"
#include "Ovni.h"
#include "Oruga.h"
#include "UnknowBall.h"
#include "Alien.h"
//Plataformas por Nivel
#include "Hell.h"
#include "Tatooine.h"
#include "montana.h"
#include "montana2.h"
#include "SpaceSus.h"
#include "Aqua.h"
//Items
#include "Muerte.h"
#include "Key.h"
#include "Portal.h"
#include "Puntos.h"
//Trampas
#include "Lava.h"
#include "Spike.h"
#include "Spike_Run.h"
#include "Spear.h"
#include "Suriken.h"
#include "Pendulum.h"
#include "Mallet.h"
#include "Fallen_Block.h"
#include "Platform_Movil.h"
#include "Erizo.h"
//Escenarios (Patron de diseño builder)
#include "SceneryDirector.h"
#include "Scenery_Tatooine.h"
#include "Scenery_Hell.h"
#include "Scenary_LLuvia.h"
#include "Scenery_Space.h"
#include "Scenery_Aqua.h"
//Otros
#include "Excepcion.h"
#include "EnemyDeath.h"
#include "PuntosSobrecarga.h"
#include "Punk_1.h"
#include "Punk_2.h"

using std::cout;
using std::endl;

struct window
{
    const int W = 1280;
    const int H = 720;
}pantalla;

bool CARGANDO = true; //CARGAR ENEMIGOS Y PLATAFORMAS
int LEVEL = 0; //CAMBIO DE NIVEL

EnemyDeath enemigo_muerte_1 = EnemyDeath(true);
EnemyDeath enemigo_muerte_2 = EnemyDeath(false);

bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);//Comparador de pares de puntuacion
bool detectar_portal(const std::vector<Item*>& portal);
bool detectar_llave(const std::vector<Item*>& llave);
void borrar_balas(Player& p1, Player& p2, std::vector<Enemy*>& enemigos);
void borrar_objetos(std::vector<Item*>& items, std::vector<Traps*>& trampas, std::vector<Enemy*>& enemigo, std::vector<Platform*>& plataformas, std::vector<Platform*>& des_plataformas);
void ejecutar_nivel(sf::RenderWindow& App, Player* jugador1, Player* jugador2, std::vector<Platform*>& vec_plataformas, 
    std::vector<Platform*>& vec_unlock_plataformas,std::vector<Enemy*>& vec_enemigos, std::vector<Traps*>& vec_trampas, std::vector<Item*>& vec_items);
std::pair<std::string, int> mayor_puntaje_jugador(Player*, Player*);

int main()
{
    sf::RenderWindow App(sf::VideoMode(pantalla.W, pantalla.H, 32), "Juego");
    App.setFramerateLimit(60);
    bool fullscream = false;

    sf::Music ms, ms_final;
    ms.openFromFile("data\\music\\main.ogg");
    ms.setVolume(20.f);
    ms_final.openFromFile("data\\music\\crash.ogg");

    //PUNTUACIONES
    std::fstream userdata("userdata.dat", std::ios::in | std::ios::out | std::ios::binary); //Extraer niveles desbloqueados y puntuaciones
    int maxUnlockedLevel{ 0 }; //PERMISOS DE NIVEL "Niveles desbloqueados"
    std::vector<std::pair<std::string, int>> puntuaciones;
    if (!userdata) {
        std::ofstream crear_archivo("userdata.dat", std::ios::out | std::ios::binary);
        puntuaciones.clear();
        puntuaciones.resize(5);
        for (auto& i : puntuaciones) {
            i.first = "None";
            i.second = 0;
        }
        crear_archivo.close();
    }
    else {
        puntuaciones.resize(5);
        if (userdata.is_open()) {
            userdata >> maxUnlockedLevel;
            for (auto& i : puntuaciones) userdata >> i.first >> i.second;
            userdata.close();
        }
    }

    //Contenedores
    std::vector<Item*> vec_items;
    std::vector<Traps*> vec_trampas;
    std::vector<Enemy*> vec_enemigos;
    std::vector<Platform*> vec_plataformas;
    std::vector<Platform*> vec_unlock_plataformas; //plataformas que se pueden eliminar al recoger la llave

    //JUGADOR
    Player* jugador1 = new Punk_1();
    Player* jugador2 = new Punk_2();
    jugador1->initialize(50.f, pantalla.H - 150.f, 3.85f, 3.5f);
    jugador1->setScale(2.5f, 2.5f);
    jugador2->initialize(50.f, pantalla.H - 150.f, 3.5f, 3.5f);
    jugador2->setScale(2.5f, 2.5f);

    //RELOJ SPAWN
    sf::Clock tiempo_spawn, tiempo_spawn_2;
    bool una_vez = false;
    bool una_vez_2 = false;
    bool una_vez_3 = false;
    bool llave = false;

    SceneryDirector* escenario = new SceneryDirector; //Patron Builder
    SceneryBuilder* escenario_infierno = new Scenery_Hell;
    SceneryBuilder* escenario_tatooine = new Scenery_Tatooine;
    SceneryBuilder* escenario_montana = new Scenary_Lluvia;
    SceneryBuilder* escenario_space = new Scenery_Space;
    SceneryBuilder* escenario_aqua = new Scenery_Aqua;

    //PUNTAJES
    //PANTALLA FINAL
    sf::Clock cuenta;
    sf::Text texto_final, texto_creditos, texto_ganador, texto_ending, puntaje_jugador_1, puntaje_jugador_2;
    sf::Font font;
    font.loadFromFile("data\\fonts\\Baskic8.otf");
    texto_final.setFont(font);
    texto_ganador.setFont(font);
    texto_ending.setFont(font);
    puntaje_jugador_1.setFont(font);
    puntaje_jugador_2.setFont(font);
    texto_creditos.setFont(font);

    texto_final.setCharacterSize(50);
    texto_final.setFillColor(sf::Color::Red);
    texto_final.setPosition(pantalla.W / 2 - 300.f, pantalla.H / 2 - 300.f);

    texto_creditos.setCharacterSize(20);
    texto_creditos.setFillColor(sf::Color::Green);
    texto_creditos.setPosition(0.f, 0.f);

    texto_ganador.setCharacterSize(65);
    texto_ganador.setFillColor(sf::Color::Blue);
    texto_ganador.setPosition(pantalla.W / 2 - 275.f, pantalla.H / 2 - 100.f);

    texto_ending.setCharacterSize(40);
    texto_ending.setFillColor(sf::Color::White);
    texto_ending.setPosition(pantalla.W / 2 - 570.f, pantalla.H / 2 + 150.f);

    puntaje_jugador_1.setCharacterSize(40);
    puntaje_jugador_1.setFillColor(sf::Color::Red);
    puntaje_jugador_1.setPosition(100.f, 40.f);
    puntaje_jugador_2.setCharacterSize(40);
    puntaje_jugador_2.setFillColor(sf::Color::Blue);
    puntaje_jugador_2.setPosition(pantalla.W - 200.f, 40.f);

    bool texto_una_vez = true;

    //static bool Coordeb{ false }; //Crea el booleano para activar y desactivar el "modo debug" 
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
                    App.create(sf::VideoMode(pantalla.W, pantalla.H, 32), "Juego", sf::Style::Fullscreen);
                    App.setFramerateLimit(60);
                    fullscream = true;
                }
                else if (ev.key.code == sf::Keyboard::Escape && fullscream == true)
                {
                    App.create(sf::VideoMode(pantalla.W, pantalla.H, 32), "Juego");
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
        try { // ->Uso del manejo de excepcion

            if (LEVEL == 0) {
                ms.play();
                Menu* menu = new Menu(puntuaciones,maxUnlockedLevel);
                menu->run_menu(App, LEVEL);
                delete menu;
                menu = nullptr;
            }
            else if (LEVEL == 1) {
                if (CARGANDO) {
                    ms.stop();
                    cout << "Cargando una vez elementos en level " << LEVEL << endl;
                    jugador1->colision_windows(pantalla.W, pantalla.H);
                    jugador2->colision_windows(pantalla.W, pantalla.H);
                    jugador1->setPosition(50.f, pantalla.H - 100.f);
                    jugador2->setPosition(100.f, pantalla.H - 100.f);
                    float xF1{ 0.2f }, yF1{ 0.2f }; //variables para la plateforma

                    //Creacion de Plataforma
                    for (int i = 0; i < 14; i++) {
                        //Piso
                        if (i > 3 && i < 9) {
                            if (i > 3 && i < 6) {
                                Traps* bloque = new Fallen_Block;
                                bloque->Inicialize(pantalla.W / 2 - 1720.f + 375.f * i, 0.f, 0.f, 5.f);
                                bloque->setScale(0.55f, 0.55f);
                                vec_trampas.push_back(bloque);
                            }
                            continue;
                        }

                        if (i == 3) {
                            Platform* piso2 = new Tatooine;
                            piso2->initialize();
                            piso2->generar_bloque_1();
                            piso2->setScale(xF1, yF1);
                            piso2->setPosition(i * piso2->getTamSprite_X() * xF1, pantalla.H - piso2->getTamSprite_Y() * yF1 * 1.5f);
                            vec_plataformas.push_back(piso2);
                        }

                        Platform* piso = new Tatooine;
                        piso->initialize();
                        piso->generar_bloque_1();
                        piso->setScale(xF1, yF1);
                        piso->setPosition(i * piso->getTamSprite_X() * xF1, pantalla.H - piso->getTamSprite_Y() * yF1 * 0.5);
                        vec_plataformas.push_back(piso);
                    }
                    
                    Traps* plataforma_movil = new Platform_Movil;
                    plataforma_movil->Inicialize(pantalla.W / 2 - 100.f, pantalla.H - 50.f, 0.f, -2.5f);
                    plataforma_movil->setScale(3.f, 3.f);
                    vec_trampas.push_back(plataforma_movil);
                    Traps* plataforma_movil2 = new Platform_Movil;
                    plataforma_movil2->Inicialize(pantalla.W / 2 + 50.f, 0.f, 0.f, 2.5f);
                    plataforma_movil2->setScale(3.f, 3.f);
                    vec_trampas.push_back(plataforma_movil2);

                    for (int i = 1; i < 4; i++) {
                        for (int j = 1; j < 4; j++) {
                            Item* item_puntos = new Puntos;
                            item_puntos->inicialize(pantalla.W / 2 - 100.f + 50.f * i, pantalla.H / 2 - 400.f + 60.f*j);
                            item_puntos->setScale(0.9f, 0.9f);
                            vec_items.push_back(item_puntos);
                        }
                    }

                    Traps* mazo = new Mallet;
                    mazo->Inicialize(pantalla.W / 2 - 100, pantalla.H - 30, 3.f);
                    mazo->setScale(0.75f, 0.75f);
                    vec_trampas.push_back(mazo);
                    Traps* mazo2 = new Mallet;
                    mazo2->Inicialize(pantalla.W / 2 + 150, pantalla.H - 30, -3.f);
                    mazo2->setScale(0.75f, 0.75f);
                    vec_trampas.push_back(mazo2);

                    //Enemigo
                    Enemy* ovni1 = new Ovni;
                    ovni1->initialize(pantalla.W - 100.f, 0.f, 2.15f, 15.f);
                    ovni1->setScale(4.5f, 4.5f);
                    vec_enemigos.push_back(ovni1);
                    Enemy* ovni2 = new Ovni;
                    ovni2->initialize(50.f, 0.f, 2.15f, 15.f);
                    ovni2->setScale(4.5f, 4.5f);
                    vec_enemigos.push_back(ovni2);

                    Item* item_portal = new Portal;
                    item_portal->inicialize(pantalla.W - 100.f, pantalla.H - 200.f);
                    item_portal->setScale(1.5f, 1.5f);
                    vec_items.push_back(item_portal);

                    escenario->setBuilder(escenario_tatooine);
                    escenario->construir_Scenary();

                    tiempo_spawn.restart();
                    CARGANDO = false;
                }
                else {
                    App.clear();

                    puntaje_jugador_1.setString("P1: " + std::to_string(jugador1->puntaje.getTotal()));
                    puntaje_jugador_2.setString("P2: " + std::to_string(jugador2->puntaje.getTotal()));

                    escenario->draw_scenary(App);
                    escenario->reproducir_musica();
                    jugador1->colision_windows(pantalla.W, pantalla.H);
                    jugador2->colision_windows(pantalla.W, pantalla.H);
                    jugador1->revivir(50.f, pantalla.H - 100.f);
                    jugador2->revivir(100.f, pantalla.H - 100.f);

                    App.draw(puntaje_jugador_1);
                    App.draw(puntaje_jugador_2);

                    ejecutar_nivel(App, jugador1, jugador2, vec_plataformas, vec_unlock_plataformas, vec_enemigos, vec_trampas, vec_items);

                    if (tiempo_spawn.getElapsedTime().asSeconds() > 20.f) {
                        //Enemigo
                        Enemy* ovni1 = new Ovni;
                        ovni1->initialize(pantalla.W - 100.f, 0.f, 2.15f, 15.f);
                        ovni1->setScale(4.5f, 4.5f);
                        vec_enemigos.push_back(ovni1);
                        Enemy* ovni2 = new Ovni;
                        ovni2->initialize(50.f, 0.f, 2.15f, 15.f);
                        ovni2->setScale(4.5f, 4.5f);
                        vec_enemigos.push_back(ovni2);
                        tiempo_spawn.restart();
                    }

                    if (detectar_portal(vec_items)) {
                        LEVEL = 2;
                        puntuaciones[0] = mayor_puntaje_jugador(jugador1, jugador2);
                        borrar_balas(*jugador1, *jugador2, vec_enemigos);
                        borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
                        escenario->parar_musica();
                        CARGANDO = true;
                    }
                }
            }
            else if (LEVEL == 2) {
                if (CARGANDO) {
                    ms.stop();
                    cout << "Cargando una vez elementos en level " << LEVEL << endl;
                    jugador1->setPosition(pantalla.W / 2, pantalla.H - 100.f);
                    jugador2->setPosition(pantalla.W / 2, pantalla.H - 100.f);

                    for (int i = 1; i < 21; i++)
                    {
                        if (i == 2) {
                            Platform* piso_plat1 = new Aqua;
                            piso_plat1->initialize();
                            piso_plat1->generar_bloque_2();
                            piso_plat1->setPosition(piso_plat1->getTamSprite_X()* i * 0.25f, pantalla.H / 2 + piso_plat1->getTamSprite_Y() * 0.5f);
                            piso_plat1->setScale(0.5f, 0.5f);
                            vec_plataformas.push_back(piso_plat1);

                            for (int g = 1; g < 5; g++) {
                                for (int j = 1; j < 3; j++) {
                                    //PUNTOS
                                    Item* puntos = new Puntos;
                                    puntos->inicialize(piso_plat1->getTamSprite_X() * g * 0.15f + 75.f, pantalla.H / 2 + piso_plat1->getTamSprite_Y() * 0.25f * j - 50.f);
                                    puntos->setScale(0.9f, 0.9f);
                                    vec_items.push_back(puntos);
                                }
                            }
                        }

                        if (i == 19) {
                            Platform* piso_plat1 = new Aqua;
                            piso_plat1->initialize();
                            piso_plat1->generar_bloque_2();
                            piso_plat1->setPosition(piso_plat1->getTamSprite_X() * i * 0.25f, pantalla.H / 2 + piso_plat1->getTamSprite_Y() * 0.5f);
                            piso_plat1->setScale(0.5f, 0.5f);
                            vec_plataformas.push_back(piso_plat1);

                            for (int g = 1; g < 5; g++) {
                                for (int j = 1; j < 4; j++) {
                                    //PUNTOS
                                    Item* puntos = new Puntos;
                                    puntos->inicialize(piso_plat1->getTamSprite_X() * g * 0.15f + 1050.f, pantalla.H / 2 + piso_plat1->getTamSprite_Y() * 0.25f * j - 105.f);
                                    puntos->setScale(0.9f, 0.9f);
                                    vec_items.push_back(puntos);
                                }
                            }
                        }

                        if (i > 3 && i < 7) {
                            Platform* piso_plat1 = new Aqua;
                            piso_plat1->initialize();
                            piso_plat1->generar_bloque_2();
                            piso_plat1->setPosition(piso_plat1->getTamSprite_X()* i * 0.5, pantalla.H - piso_plat1->getTamSprite_Y() * 0.25f);
                            piso_plat1->setScale(0.5f, 0.5f);
                            vec_plataformas.push_back(piso_plat1);                

                            if (i == 5) {
                                Platform* piso_plat2 = new Aqua;
                                piso_plat2->initialize();
                                piso_plat2->generar_bloque_2();
                                piso_plat2->setPosition(piso_plat2->getTamSprite_X()* i * 0.5, piso_plat2->getTamSprite_Y());
                                piso_plat2->setScale(0.5f, 0.5f);
                                vec_plataformas.push_back(piso_plat2);

                                Item* item_llave = new Key;
                                item_llave->inicialize(piso_plat2->getTamSprite_X()* i * 0.5 + 50.f, piso_plat2->getTamSprite_Y() - 50.f);
                                item_llave->setScale(0.55f, 0.55f);
                                vec_items.push_back(item_llave);
                            }
                            else if (i == 4) {
                                Traps* plataforma_movil2 = new Platform_Movil;
                                plataforma_movil2->Inicialize(piso_plat1->getTamSprite_X() * i * 0.5 - 100.f, piso_plat1->getTamSprite_Y(), 0.f, 3.5f);
                                plataforma_movil2->setScale(3.f, 3.f);
                                vec_trampas.push_back(plataforma_movil2);
                            }
                            else if (i == 6) {
                                Traps* plataforma_movil3 = new Platform_Movil;
                                plataforma_movil3->Inicialize(piso_plat1->getTamSprite_X() * i * 0.5 + 120.f, piso_plat1->getTamSprite_Y(), 0.f, -3.5f);
                                plataforma_movil3->setScale(3.f, 3.f);
                                vec_trampas.push_back(plataforma_movil3);
                            }
                        }

                        if (i < 5 || i > 16) {
                            Platform* piso_plat1 = new Aqua;
                            piso_plat1->initialize();
                            piso_plat1->generar_bloque_3();
                            piso_plat1->setPosition(piso_plat1->getTamSprite_X()* i * 0.5, pantalla.H / 2 - piso_plat1->getTamSprite_Y() * 0.5f * 2.f);
                            piso_plat1->setScale(0.5f, 0.5f);
                            vec_plataformas.push_back(piso_plat1);
                        }

                        if (i == 14 || i == 3) {
                            Platform* piso_plat1 = new Aqua;
                            piso_plat1->initialize();
                            piso_plat1->generar_bloque_4();
                            piso_plat1->setPosition(piso_plat1->getTamSprite_X()* i * 0.5, pantalla.H / 2 - piso_plat1->getTamSprite_Y() * 0.85f);
                            piso_plat1->setScale(0.5f, 0.5f);
                            vec_unlock_plataformas.push_back(piso_plat1);

                            if (i == 3) {
                                Item* item_portal = new Portal;
                                item_portal->inicialize(piso_plat1->getTamSprite_X() * i * 0.5 - 170.f, pantalla.H / 2 - piso_plat1->getTamSprite_Y() * 0.85f);
                                item_portal->setScale(1.5f, 1.5f);
                                vec_items.push_back(item_portal);
                            }

                            else if (i == 14) {
                                Item* item_puntos = new PuntosSobrecarga;
                                item_puntos->inicialize(piso_plat1->getTamSprite_X() * i * 0.5 + 200.f, pantalla.H / 2 - piso_plat1->getTamSprite_Y() * 0.85f + 110.f);
                                item_puntos->setScale(0.9f, 0.9f);
                                vec_items.push_back(item_puntos);
                            }
                        }   
                    }

                    for (int i = 0; i < 24; i++) {
                        Traps* erizo = new Erizo;
                        erizo->Inicialize(i * 80.f * 0.65f, 0.f);
                        erizo->setScale(0.65f, 0.65f);
                        vec_trampas.push_back(erizo);
                        if (i < 9 || i > 14) {
                            Traps* erizo = new Erizo;
                            erizo->Inicialize(i * 80.f * 0.65f, pantalla.H - 40.f);
                            erizo->setScale(0.65f, 0.65f);
                            vec_trampas.push_back(erizo);
                        }
                    }

                    for (int i = 1; i < 20; i++) {
                        Traps* erizo = new Erizo;
                        erizo->Inicialize(0.f, i * 80.f * 0.65f);
                        erizo->setScale(0.65f, 0.65f);
                        vec_trampas.push_back(erizo);

                        Traps* erizo2 = new Erizo;
                        erizo2->Inicialize(pantalla.W - 70.f, i * 80.f * 0.65f);
                        erizo2->setScale(0.65f, 0.65f);
                        vec_trampas.push_back(erizo2);
                    }

                    Enemy* buceo = new Buceo;
                    buceo->initialize(pantalla.W - 30.f, 30.f, 2.25f, 2.25f);
                    buceo->setScale(2.5f, 2.5f);
                    vec_enemigos.push_back(buceo);
                    Enemy* buceo2 = new Buceo;
                    buceo2->initialize(0.f, pantalla.H - 30.f, 2.25f, 2.25f);
                    buceo2->setScale(2.5f, 2.5f);
                    vec_enemigos.push_back(buceo2);
                    Enemy* submarino = new Submarino;
                    submarino->initialize(pantalla.W / 2, pantalla.H / 2, 2.25f);
                    submarino->setScale(2.5f, 2.5f);
                    vec_enemigos.push_back(submarino);

                    escenario->setBuilder(escenario_aqua);
                    escenario->construir_Scenary();
                    CARGANDO = false;

                    tiempo_spawn.restart();
                }
                else {
                    App.clear();

                    puntaje_jugador_1.setString("P1: " + std::to_string(jugador1->puntaje.getTotal()));
                    puntaje_jugador_2.setString("P2: " + std::to_string(jugador2->puntaje.getTotal()));

                    escenario->draw_scenary(App);
                    escenario->reproducir_musica();
                    jugador1->colision_windows(pantalla.W, pantalla.H);
                    jugador2->colision_windows(pantalla.W, pantalla.H);
                    jugador1->revivir(pantalla.W / 2, pantalla.H - 100.f);
                    jugador2->revivir(pantalla.W / 2, pantalla.H - 100.f);

                    App.draw(puntaje_jugador_1);
                    App.draw(puntaje_jugador_2);

                    ejecutar_nivel(App, jugador1, jugador2, vec_plataformas, vec_unlock_plataformas, vec_enemigos, vec_trampas, vec_items);

                    if (tiempo_spawn.getElapsedTime().asSeconds() > 17.f) {
                        Enemy* buceo = new Buceo;
                        buceo->initialize(pantalla.W - 30.f, 30.f, 2.25f, 2.25f);
                        buceo->setScale(2.5f, 2.5f);
                        vec_enemigos.push_back(buceo);
                        Enemy* buceo2 = new Buceo;
                        buceo2->initialize(0.f, pantalla.H - 30.f, 2.25f, 2.25f);
                        buceo2->setScale(2.5f, 2.5f);
                        vec_enemigos.push_back(buceo2);
                        Enemy* buceo3 = new Buceo;
                        buceo3->initialize(pantalla.W - 30.f, pantalla.H - 30.f, 2.25f, 2.25f);
                        buceo3->setScale(2.5f, 2.5f);
                        vec_enemigos.push_back(buceo3);
                        tiempo_spawn.restart();
                    }

                    if (detectar_llave(vec_items) && !una_vez_3) {
                        Enemy* submarino1 = new Submarino;
                        submarino1->initialize(400.f, 100.f, 0.f, 2.25f);
                        submarino1->setScale(2.5f, 2.5f);
                        vec_enemigos.push_back(submarino1);
                        Enemy* submarino2 = new Submarino;
                        submarino2->initialize(pantalla.W - 400.f, 100.f, 0.f, -2.25f);
                        submarino2->setScale(2.5f, 2.5f);
                        vec_enemigos.push_back(submarino2);

                        Enemy* submarino3 = new Submarino;
                        submarino3->initialize(pantalla.W / 2, pantalla.H / 2, 2.25f);
                        submarino3->setScale(2.5f, 2.5f);
                        vec_enemigos.push_back(submarino3);
                        una_vez_3 = true;
                    }

                    if (detectar_portal(vec_items)) {
                        LEVEL = 3;
                        puntuaciones[1] = mayor_puntaje_jugador(jugador1, jugador2);
                        borrar_balas(*jugador1, *jugador2, vec_enemigos);
                        borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
                        escenario->parar_musica();
                        CARGANDO = true;
                    }
                }
            }
            else if (LEVEL == 3) {
                if (CARGANDO) {
                    ms.stop();
                    cout << "Cargando una vez elementos en level " << LEVEL << endl;
                    float xF1{ 1.2f }, yF1{ 1.f };
                    jugador1->setPosition(0.f, 0.f);
                    jugador2->setPosition(pantalla.W - 50.f, 0.0f);
                    escenario->setBuilder(escenario_montana);
                    escenario->construir_Scenary();

                    for (int i = 1; i < 30; i++)
                    {
                        Platform* piso_plat1 = new montana;
                        piso_plat1->initialize();
                        piso_plat1->generar_bloque_1();
                        piso_plat1->setScale(xF1, yF1);
                        piso_plat1->setPosition(piso_plat1->getTamSprite_X() * (i-1), pantalla.H - piso_plat1->getTamSprite_Y());
                        vec_plataformas.push_back(piso_plat1);
                    }

                    for (int i = 1; i < 30; i++)
                    {
                        if (i > 12 && i < 16) {
                            Platform* Muro = new Hell;
                            Muro->initialize();
                            Muro->generar_bloque_3();
                            Muro->setScale(1.7f, 1.7f);
                            Muro->setPosition(Muro->getTamSprite_X() * 1.75 * (i-3), pantalla.H / 2 + Muro->getTamSprite_Y() * 0.75);
                            vec_unlock_plataformas.push_back(Muro);
                            continue;
                        }
                        Platform* piso_plat1 = new montana;
                        piso_plat1->initialize();
                        piso_plat1->generar_bloque_1();
                        piso_plat1->setScale(xF1, yF1);
                        piso_plat1->setPosition(piso_plat1->getTamSprite_X() * (i - 1), pantalla.H/2 + piso_plat1->getTamSprite_Y());
                        vec_plataformas.push_back(piso_plat1);
                    }
                    
                    for (int i = 1; i < 30; i++)
                    {
                        if (i > 8 && i < 20) {
                            continue;
                        }
                        Platform* piso_plat1 = new montana;
                        piso_plat1->initialize();
                        piso_plat1->generar_bloque_1();
                        piso_plat1->setScale(xF1, yF1);
                        piso_plat1->setPosition(piso_plat1->getTamSprite_X() * (i - 1), pantalla.H / 2 - piso_plat1->getTamSprite_Y()*5);
                        vec_plataformas.push_back(piso_plat1);
                    }

                    //TRAMPA
                    Traps* trampa_spikerun = new Spike_Run;
                    trampa_spikerun->Inicialize(pantalla.W / 2.f, pantalla.H - 200.f, 10.0f, 0.f);
                    trampa_spikerun->setScale(2.5f, 2.5f);
                    vec_trampas.push_back(trampa_spikerun);

                    Enemy* enemigo_fungus3 = new Fungus;
                    Enemy* enemigo_fungus4 = new Fungus;
                    enemigo_fungus3->initialize(pantalla.W - 80.f, pantalla.H - 200.f, 3.25f, 2.f);
                    enemigo_fungus4->initialize(60.f, pantalla.H - 200.f, 3.25f, 2.f);
                    enemigo_fungus3->setScale(2.5f, 2.5f);
                    enemigo_fungus4->setScale(2.5f, 2.5f);
                    Enemy* enemigo_oruga3 = new Oruga;
                    Enemy* enemigo_oruga4 = new Oruga;
                    enemigo_oruga3->initialize(pantalla.W - 200.f, pantalla.H / 2 - 200.f, 1.f);
                    enemigo_oruga4->initialize(60.f, pantalla.H / 2 - 200.f, 1.f);
                    enemigo_oruga3->setScale(4.5f, 4.5f);
                    enemigo_oruga4->setScale(4.5f, 4.5f);
                    vec_enemigos.push_back(enemigo_fungus3);
                    vec_enemigos.push_back(enemigo_fungus4);
                    vec_enemigos.push_back(enemigo_oruga3);
                    vec_enemigos.push_back(enemigo_oruga4);

                    //LLAVE 
                    Item* item_llave = new Key;
                    item_llave->inicialize(0.f, pantalla.H / 2);
                    item_llave->setScale(0.55f, 0.55f);
                    vec_items.push_back(item_llave);


                    for (int i = 1; i < 6; i++) {
                        for (int j = 1; j < 3; j++) {
                            //PUNTOS
                            Item* puntos = new Puntos;
                            puntos->inicialize(pantalla.W - (40.f) * i, pantalla.H * 0.58 - (60.f) * j);
                            puntos->setScale(0.9f, 0.9f);
                            vec_items.push_back(puntos);
                        }
                    }

                    //PORTAL
                    Item* item_portal = new Portal;
                    item_portal->inicialize(1200, 500);
                    item_portal->setScale(1.5f, 1.5f);
                    vec_items.push_back(item_portal);
                    CARGANDO = false;

                    tiempo_spawn.restart();
                }
                else {
                    App.clear();

                    escenario->draw_scenary(App);
                    escenario->reproducir_musica();

                    jugador1->colision_windows(pantalla.W, pantalla.H);
                    jugador2->colision_windows(pantalla.W, pantalla.H);
                    jugador1->revivir(0.f, 0.f);
                    jugador2->revivir(pantalla.W - 50.f, 0.0f);

                    puntaje_jugador_1.setString("P1: " + std::to_string(jugador1->puntaje.getTotal()));
                    puntaje_jugador_2.setString("P2: " + std::to_string(jugador2->puntaje.getTotal()));

                    App.draw(puntaje_jugador_1);
                    App.draw(puntaje_jugador_2);

                    ejecutar_nivel(App, jugador1, jugador2, vec_plataformas, vec_unlock_plataformas, vec_enemigos, vec_trampas, vec_items);

                    if (tiempo_spawn.getElapsedTime().asSeconds() > 14.f) {
                        Enemy* enemigo_fungus = new Fungus;
                        Enemy* enemigo_fungus2 = new Fungus;
                        enemigo_fungus->initialize(pantalla.W - 100.f, pantalla.H - 200.f, 3.25f, 2.f);
                        enemigo_fungus2->initialize(20.f, pantalla.H - 200.f, 3.25f, 2.f);
                        enemigo_fungus->setScale(2.5f, 2.5f);
                        enemigo_fungus2->setScale(2.5f, 2.5f);
                        Enemy* enemigo_oruga = new Oruga;
                        Enemy* enemigo_oruga2 = new Oruga;
                        enemigo_oruga->initialize(pantalla.W - 200.f, pantalla.H / 2 - 200.f, 1.f);
                        enemigo_oruga2->initialize(20.f, pantalla.H / 2 - 200.f, 1.f);
                        enemigo_oruga->setScale(4.5f, 4.5f);
                        enemigo_oruga2->setScale(4.5f, 4.5f);
                        vec_enemigos.push_back(enemigo_fungus);
                        vec_enemigos.push_back(enemigo_fungus2);
                        vec_enemigos.push_back(enemigo_oruga);
                        vec_enemigos.push_back(enemigo_oruga2);
           
                        if (detectar_llave(vec_items)) {
                            Enemy* enemigo_oruga3 = new Oruga;
                            Enemy* enemigo_oruga4 = new Oruga;
                            enemigo_oruga3->initialize(pantalla.W - 300.f, pantalla.H / 2 - 200.f, 1.f);
                            enemigo_oruga4->initialize(120.f, pantalla.H / 2 - 200.f, 1.f);
                            enemigo_oruga3->setScale(4.5f, 4.5f);
                            enemigo_oruga4->setScale(4.5f, 4.5f);
                            vec_enemigos.push_back(enemigo_oruga3);
                            vec_enemigos.push_back(enemigo_oruga4);
                        }                     
                        tiempo_spawn.restart();
                    }

                    if (detectar_portal(vec_items)) {
                        LEVEL = 4;
                        puntuaciones[2] = mayor_puntaje_jugador(jugador1, jugador2);
                        escenario->parar_musica();
                        borrar_balas(*jugador1, *jugador2, vec_enemigos);
                        borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
                        CARGANDO = true;
                        tiempo_spawn.restart();
                    }
                }
            }
            else if (LEVEL == 4) {
                if (CARGANDO) {
                    ms.stop();           
                    jugador1->setPosition(520, 400);
                    jugador2->setPosition(700, 400);

                    //Creación de plataformas estáticas
                    for (int i = 1; i < 10; i++) {             
                        Item* item_puntos = new Puntos;
                        item_puntos->inicialize(310, i * 57);
                        item_puntos->setScale(0.85f, 0.85f);
                        vec_items.push_back(item_puntos);
                        Item* item_puntos2 = new Puntos;
                        item_puntos2->inicialize(950, i * 57);
                        item_puntos2->setScale(0.85f, 0.85f);
                        vec_items.push_back(item_puntos2);
                    }

                    for (int i = 0; i < 20; i++) {
                        if (i > 8 && i < 12) {
                            Platform* Muro = new SpaceSus;
                            Muro->initialize();
                            Muro->generar_bloque_1();
                            Muro->setScale(2.f, 2.f);
                            Muro->setPosition(pantalla.W / 2 - Muro->getTamSprite_X() * 2.f * (i - 9), pantalla.H - Muro->getTamSprite_Y() * 3);
                            vec_plataformas.push_back(Muro);                       
                            Platform* Muro2 = new SpaceSus;
                            Muro2->initialize();
                            Muro2->generar_bloque_1();
                            Muro2->setScale(2.f, 2.f);
                            Muro2->setPosition(pantalla.W / 2 - Muro->getTamSprite_X() * 2.f * (i - 9), pantalla.H - Muro->getTamSprite_Y() * 5);
                            vec_plataformas.push_back(Muro2);                      
                        }

                        Platform* Suelo = new SpaceSus;
                        Suelo->initialize();
                        Suelo->generar_bloque_3();
                        Suelo->setScale(2.f, 2.f);
                        Suelo->setPosition(Suelo->getTamSprite_X() * 2.f * i, pantalla.H - Suelo->getTamSprite_Y());
                        vec_plataformas.push_back(Suelo);
                    }

                    for (int i = 0; i < 8; i++) {
                        Platform* Suelo2 = new SpaceSus;
                        Suelo2->initialize();
                        Suelo2->generar_bloque_4();
                        Suelo2->setScale(1.8, 1.5);
                        Suelo2->setPosition(400 + i * 60, 300);
                        vec_plataformas.push_back(Suelo2);
                    }

                    for (int i = 0; i < 4; i++) {
                        Platform* Suelo3 = new SpaceSus;
                        Suelo3->initialize();
                        Suelo3->generar_bloque_3();
                        Suelo3->setScale(1.8, 1.5);
                        Suelo3->setPosition(520 + i * 60, 150);
                        vec_plataformas.push_back(Suelo3);
                    }

                    //Plataforma movible
                    Traps* plataforma_movil2 = new Platform_Movil;
                    plataforma_movil2->Inicialize(277, 0, 0.f, 3.5f);
                    plataforma_movil2->setScale(3.f, 3.f);
                    vec_trampas.push_back(plataforma_movil2);

                    Traps* plataforma_movil3 = new Platform_Movil;
                    plataforma_movil3->Inicialize(930, 466, 0.f, 3.5f);
                    plataforma_movil3->setScale(3.f, 3.f);
                    vec_trampas.push_back(plataforma_movil3);

                    //Items
                    Item* item_llave = new Key;
                    item_llave->inicialize(636, 240);
                    item_llave->setScale(0.55f, 0.55f);
                    vec_items.push_back(item_llave);

                    //Paredes desbloqueables
                    for (int i = 0; i < 2; i++)
                    {
                        Platform* Muro = new SpaceSus;
                        Muro->initialize();
                        Muro->generar_bloque_1();
                        Muro->setScale(2.f, 2.f);
                        Muro->setPosition(520, 86 - 60 * i);
                        vec_unlock_plataformas.push_back(Muro);

                        Platform* Muro2 = new SpaceSus;
                        Muro2->initialize();
                        Muro2->generar_bloque_1();
                        Muro2->setScale(2.f, 2.f);
                        Muro2->setPosition(700, 86 - 60 * i);
                        vec_unlock_plataformas.push_back(Muro2);
                    }

                    //Portal END
                    Item* item_portal = new Portal;
                    item_portal->inicialize(600, 0);
                    item_portal->setScale(1.5f, 1.5f);
                    vec_items.push_back(item_portal);
                    //Enemigos
                    Enemy* unknow_ball = new UnknowBall;
                    unknow_ball->initialize(300.f, 100.f , 0.f, 2.5f);
                    unknow_ball->setScale(4.f, 4.f);
                    vec_enemigos.push_back(unknow_ball);
                    Enemy* unknow_ball2 = new UnknowBall;
                    unknow_ball2->initialize(1000.f, 100.f, 0.f, -2.5f);
                    unknow_ball2->setScale(4.f, 4.f);
                    vec_enemigos.push_back(unknow_ball2);

                    Enemy* unknow_ball3 = new UnknowBall;
                    unknow_ball3->initialize(200.f, 200.f, 0.f, 2.5f);
                    unknow_ball3->setScale(4.f, 4.f);
                    vec_enemigos.push_back(unknow_ball3);

                    Enemy* unknow_ball4 = new UnknowBall;
                    unknow_ball4->initialize(1100, 200.f, 0.f, -2.5f);
                    unknow_ball4->setScale(4.f, 4.f);
                    vec_enemigos.push_back(unknow_ball4);
                    Enemy* unknow_ball5 = new UnknowBall;
                    unknow_ball5->initialize(100.f, 300.f, 0.f, 2.5f);
                    unknow_ball5->setScale(4.f, 4.f);
                    vec_enemigos.push_back(unknow_ball5);
                    Enemy* unknow_ball6 = new UnknowBall;
                    unknow_ball6->initialize(900, 0.f, 0.f, -2.5f);
                    unknow_ball6->setScale(4.f, 4.f);
                    vec_enemigos.push_back(unknow_ball6);

                    //Construccion de escenario
                    escenario->setBuilder(escenario_space);
                    escenario->construir_Scenary();
                    CARGANDO = false;
                }
                else {
                    App.clear();
                    escenario->draw_scenary(App);
                    escenario->reproducir_musica();
                    jugador1->colision_windows(pantalla.W, pantalla.H);
                    jugador2->colision_windows(pantalla.W, pantalla.H);
                    jugador1->revivir(pantalla.W / 2 - 200.f, pantalla.H - 100.f);
                    jugador2->revivir(pantalla.W / 2 + 100.f, pantalla.H - 100.f);

                    puntaje_jugador_1.setString("P1: " + std::to_string(jugador1->puntaje.getTotal()));
                    puntaje_jugador_2.setString("P2: " + std::to_string(jugador2->puntaje.getTotal()));

                    App.draw(puntaje_jugador_1);
                    App.draw(puntaje_jugador_2);

                    ejecutar_nivel(App, jugador1, jugador2, vec_plataformas, vec_unlock_plataformas, vec_enemigos, vec_trampas, vec_items);

                    if (tiempo_spawn.getElapsedTime().asSeconds() > 22.f) {
                        Enemy* enemigo_thrower_3 = new Throwingfire;
                        Enemy* enemigo_thrower_4 = new Throwingfire;
                        enemigo_thrower_3->initialize(20.f, 400.f, 2.15f, 5.5f);
                        enemigo_thrower_3->setScale(3.f, 3.f);
                        enemigo_thrower_4->initialize(pantalla.W - 150.f, 400.f, 2.15f, 5.5f);
                        enemigo_thrower_4->setScale(3.f, 3.f);
                        vec_enemigos.push_back(enemigo_thrower_4);
                        vec_enemigos.push_back(enemigo_thrower_3);
                        tiempo_spawn.restart();
                    }

                    if (detectar_portal(vec_items)) {
                        LEVEL = 5;
                        puntuaciones[3] = mayor_puntaje_jugador(jugador1, jugador2);
                        escenario->parar_musica();
                        borrar_balas(*jugador1, *jugador2, vec_enemigos);
                        borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
                        CARGANDO = true;
                        tiempo_spawn.restart();
                        tiempo_spawn_2.restart();
                    }               
                }
            }
            else if (LEVEL == 5) {
                if (CARGANDO) {
                    ms.stop();
                    cout << "Cargando una vez elementos en level " << LEVEL << endl;
                    CARGANDO = false;
                    jugador1->setPosition(200.f, pantalla.H - 150.f);
                    jugador2->setPosition(200.f, pantalla.H - 150.f);
                    for (int i = 0; i < 2; i++)
                    {
                        Platform* Suelo = new Hell;
                        Suelo->initialize();
                        Suelo->generar_bloque_1();
                        Suelo->setScale(2.f, 2.f);
                        Suelo->setPosition(i * 76.f * 2.f, pantalla.H - 33.f);
                        vec_plataformas.push_back(Suelo);
                        Platform* Muro = new Hell;
                        Muro->initialize();
                        Muro->generar_bloque_3();
                        Muro->setScale(1.7f, 1.7f);
                        Muro->setPosition(100.f, pantalla.H - 140.f - 64.f * 1.7f * i);
                        vec_unlock_plataformas.push_back(Muro);
                    }
                    for (int i = 0; i < 8; i++)
                    {
                        if (i % 2 == 0 && i < 8)
                        {
                            Platform* Plat2 = new Hell;
                            Plat2->initialize();
                            Plat2->generar_bloque_2();
                            Plat2->setScale(2.f, 2.f);
                            Plat2->setPosition(380.f + i * 0.635f * 95.f * 2.f, pantalla.H - 50.f);
                            vec_plataformas.push_back(Plat2);
                            Item* item_puntos = new Puntos;
                            item_puntos->inicialize(380.f + i * 0.625f * 95.f * 2.f, pantalla.H - 100.f);
                            item_puntos->setScale(0.85f, 0.85f);
                            vec_items.push_back(item_puntos);
                        }
                        Traps* trampa_lava = new Lava();
                        trampa_lava->Inicialize(305.f + i * 64.f * 2.f, pantalla.H - 23.f);
                        trampa_lava->setScale(2.f, 2.f);
                        vec_trampas.push_back(trampa_lava);
                    }
                    for (int i = 0; i < 20; i++)
                    {
                        if (i < 18)
                        {
                            Platform* Plat2 = new Hell;
                            Plat2->initialize();
                            Plat2->generar_bloque_2();
                            Plat2->setScale(2.f, 2.f);
                            Plat2->setPosition(i * 32.f * 2.f, pantalla.H - 300.f);
                            vec_plataformas.push_back(Plat2);
                        }
                        if (i > 1)
                        {
                            Platform* Plat2 = new Hell;
                            Plat2->initialize();
                            Plat2->generar_bloque_2();
                            Plat2->setScale(2.f, 2.f);
                            Plat2->setPosition(i * 32.f * 2.f, pantalla.H - 530.f);
                            vec_plataformas.push_back(Plat2);
                        }
                        if (i % 2 == 0 && i < 8)
                        {
                            Item* item_puntos = new Puntos;
                            item_puntos->inicialize(200.f + i * 95.f * 2.0f, pantalla.H - 350.f);
                            item_puntos->setScale(0.85f, 0.85f);
                            vec_items.push_back(item_puntos);
                        }
                    }

                    Item* item_muerte = new Muerte;
                    item_muerte->inicialize(pantalla.W/2, pantalla.H - 580.f);
                    item_muerte->setScale(0.85f, 0.85f);
                    vec_items.push_back(item_muerte);

                    for (int i = 0; i < 2; i++)
                    {
                        Platform* Muro = new Hell;
                        Muro->initialize();
                        Muro->generar_bloque_3();
                        Muro->setScale(1.7f, 1.7f);
                        Muro->setPosition(i * 1000.f, pantalla.H - 405.f);
                        vec_plataformas.push_back(Muro);
                    }
                    Traps* plataforma_movil = new Platform_Movil;
                    plataforma_movil->Inicialize(pantalla.W - 100.f, pantalla.H / 2.f, 0.f, 3.5f);
                    plataforma_movil->setScale(3.f, 3.f);
                    vec_trampas.push_back(plataforma_movil);
                    Traps* trampa_spikerun = new Spike_Run;
                    trampa_spikerun->Inicialize(pantalla.W - 100.f, pantalla.H - 420.f, 4.5f, 0.f);
                    trampa_spikerun->setScale(2.5f, 2.5f);
                    trampa_spikerun->setRotate(180.f);
                    vec_trampas.push_back(trampa_spikerun);
                    Traps* trampa_spike = new Spike;
                    trampa_spike->Inicialize(pantalla.W - 20.f, pantalla.H / 2.f - 105.f);
                    trampa_spike->setScale(2.5f, 2.5f);
                    trampa_spike->setRotate(180.f);
                    vec_trampas.push_back(trampa_spike);
                    Item* item_llave = new Key;
                    item_llave->inicialize(pantalla.W - 50.f, 100.f);
                    item_llave->setScale(0.55f, 0.55f);
                    vec_items.push_back(item_llave);
                    Item* item_portal = new Portal;
                    item_portal->inicialize(10.f, pantalla.H - 200.f);
                    item_portal->setScale(1.5f, 1.5f);
                    vec_items.push_back(item_portal);
                    Enemy* enemigo_demon = new Demon;
                    enemigo_demon->initialize(200.f, 0.f, 1.5f);
                    enemigo_demon->setScale(1.80f, 1.65f);
                    vec_enemigos.push_back(enemigo_demon);
                    Enemy* enemigo_blodmonster = new BloodMonster;
                    enemigo_blodmonster->initialize(pantalla.W - 150.f, 10.f, 2.f);
                    enemigo_blodmonster->setScale(1.65f, 1.85f);
                    vec_enemigos.push_back(enemigo_blodmonster);
                    Enemy* enemigo_harpy = new Harpy;
                    enemigo_harpy->initialize(pantalla.W - 80.f, pantalla.H - 220.f, 2.5f, 3.f);
                    enemigo_harpy->setScale(1.5f, 1.5f);
                    vec_enemigos.push_back(enemigo_harpy);

                    escenario->setBuilder(escenario_infierno);
                    escenario->construir_Scenary();
                    CARGANDO = false;
                }
                else {
                    App.clear();
                    escenario->draw_scenary(App);
                    escenario->reproducir_musica();
                    jugador1->colision_windows(pantalla.W, pantalla.H);
                    jugador2->colision_windows(pantalla.W, pantalla.H);

                    puntaje_jugador_1.setString("P1: " + std::to_string(jugador1->puntaje.getTotal()));
                    puntaje_jugador_2.setString("P2: " + std::to_string(jugador2->puntaje.getTotal()));

                    App.draw(puntaje_jugador_1);
                    App.draw(puntaje_jugador_2);

                    ejecutar_nivel(App, jugador1, jugador2, vec_plataformas, vec_unlock_plataformas, vec_enemigos, vec_trampas, vec_items);

                    if (detectar_llave(vec_items)) {
                        jugador1->revivir(pantalla.W - 50.f, 100.f);
                        jugador2->revivir(pantalla.W - 50.f, 100.f);
                        if (!una_vez) {
                            jugador1->setPosition(pantalla.W - 50.f, 100.f);
                            jugador2->setPosition(pantalla.W - 50.f, 100.f);

                            Enemy* enemigo_demon = new Demon;
                            enemigo_demon->initialize(200.f, pantalla.H / 2 - 200.f, 1.5f);
                            enemigo_demon->setScale(1.75f, 1.75f);

                            Enemy* enemigo_demon2 = new Demon;
                            enemigo_demon2->initialize(pantalla.W / 2 + 100.f, pantalla.H/2 - 200.f, -1.5f);
                            enemigo_demon2->setScale(1.75f, 1.75f);

                            vec_enemigos.push_back(enemigo_demon);
                            vec_enemigos.push_back(enemigo_demon2);
                            una_vez = true;
                        }
                        if (tiempo_spawn.getElapsedTime().asSeconds() > 10.f) {
                            Enemy* enemigo_blodmonster = new BloodMonster;
                            enemigo_blodmonster->initialize(700.f, pantalla.H - 450.f, 2.5f);
                            enemigo_blodmonster->setScale(1.65f, 1.85f);
                            vec_enemigos.push_back(enemigo_blodmonster);
                            tiempo_spawn.restart();
                        }
                        if (tiempo_spawn_2.getElapsedTime().asSeconds() > 12.f) {
                            Enemy* enemigo_harpy = new Harpy;
                            enemigo_harpy->initialize(pantalla.W - 80.f, pantalla.H - 220.f, 2.5f, 3.f);
                            enemigo_harpy->setScale(1.5f, 1.5f);
                            vec_enemigos.push_back(enemigo_harpy);
                            tiempo_spawn_2.restart();
                        }
                    }
                    else {
                        jugador1->revivir(200.f, pantalla.H - 150.f);
                        jugador2->revivir(200.f, pantalla.H - 150.f);
                        if (tiempo_spawn.getElapsedTime().asSeconds() > 15.f) {
                            Enemy* enemigo_blodmonster = new BloodMonster;
                            enemigo_blodmonster->initialize(pantalla.W - 150.f, 10.f, 2.f);
                            enemigo_blodmonster->setScale(1.65f, 1.85f);
                            vec_enemigos.push_back(enemigo_blodmonster);
                            tiempo_spawn.restart();
                        }
                        if (tiempo_spawn_2.getElapsedTime().asSeconds() > 16.f) {
                            Enemy* enemigo_harpy = new Harpy;
                            enemigo_harpy->initialize(pantalla.W - 80.f, pantalla.H - 220.f, 2.5f, 3.f);
                            enemigo_harpy->setScale(1.5f, 1.5f);
                            vec_enemigos.push_back(enemigo_harpy);
                            tiempo_spawn_2.restart();
                        }
                    }

                    if (detectar_portal(vec_items)) {
                        LEVEL = 6;
                        escenario->parar_musica();
                        puntuaciones[4] = mayor_puntaje_jugador(jugador1, jugador2);
                        borrar_balas(*jugador1, *jugador2, vec_enemigos);
                        borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
                        CARGANDO = true;
                        cuenta.restart();
                    }               
                }
            }
            else if (LEVEL == 6) {
                App.clear();

                if (texto_una_vez) {
                    ms_final.play();
                    texto_ending.setString("Por que sigues aqui??, el juego ya se acabo y debido a la falta\n de un boton de salir, el juego se crasheara cuando\nse acabe el siguiente rolon\n");

                    texto_final.setString("\t\t\tPUNTAJES FINALES\n Jugador 1: " + std::to_string(jugador1->puntaje.getTotal())
                        + "\tJugador 2: " + std::to_string(jugador2->puntaje.getTotal()) + '\n');
                    
                    texto_creditos.setString("creado por:\n*Fan Numero 1 de Animan Studios\n*la amongas\n*Qebien\n*El Pederasta\n*dakimakura de peter girando\ncon funky town de fondo");

                    if (jugador1->puntaje.getTotal() > jugador2->puntaje.getTotal()) {
                        texto_ganador.setString("\tEL JUGADOR 1 GANA!!!\n");
                    }
                    else if (jugador1->puntaje.getTotal() < jugador2->puntaje.getTotal()) {
                        texto_ganador.setString("\tEL JUGADOR 2 GANA!!!\n");
                    }
                    else {
                        texto_ganador.setString("\tEMPATE??\n\n");
                    }
                    texto_una_vez = false;
                }
              
                App.draw(texto_ending);
                App.draw(texto_final);
                App.draw(texto_ganador);
                App.draw(texto_creditos);

                App.display();

                if (cuenta.getElapsedTime().asSeconds() > 25) {
                    throw std::exception("Esta webada esta mal programada\n");
                    cuenta.restart();
                }
            }
            else {
                throw Excepcion();
            }
        }
        catch (Excepcion& exp) {
            cout << exp.what() << endl;
            return -1;
        }

        //debug. Si quiere ser usado, debe pegarse arriba de "App.display()" dentro del nivel en el que se quiera usar.
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

    //Puntuaciones escritura en el archivo 'userdata.txt'
    //Escribir los datos
    userdata.open("userdata.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (userdata.is_open()) {
        userdata << maxUnlockedLevel << "\n";
        for (const auto& i : puntuaciones) userdata << i.first << " " << i.second << "\n";
        userdata.close();
    }
    
    //ELIMINAR OBJETOS Y LIBERAR MEMORIA
    borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
    delete jugador1, jugador2, escenario, escenario_infierno, escenario_montana, escenario_tatooine, escenario_space;
    return 0;
}

void ejecutar_nivel(sf::RenderWindow& App, Player* jugador1, Player* jugador2, std::vector<Platform*>& vec_plataformas, std::vector<Platform*>& vec_unlock_plataformas,
    std::vector<Enemy*>& vec_enemigos, std::vector<Traps*>& vec_trampas, std::vector<Item*>& vec_items) {
    bool crear_alien = false;
    float pos_x{}, pos_y{};

        for (auto& plat : vec_plataformas)
        {
            plat->draw(App);
            jugador1->colision_platform(*plat);
            jugador2->colision_platform(*plat);
            jugador1->colision_bullets(*plat, pantalla.W, pantalla.H);
            jugador2->colision_bullets(*plat, pantalla.W, pantalla.H);
            for (auto& e : vec_enemigos) {
                e->colision_platform(*plat);
                e->colision_bullets(*plat, pantalla.W, pantalla.H);
            }
            for (auto& t : vec_trampas)
                t->colision_platform_window(*plat, pantalla.W, pantalla.H);
        }

        for (auto& plat : vec_unlock_plataformas)
        {
            plat->draw(App);
            jugador1->colision_platform(*plat);
            jugador2->colision_platform(*plat);
            jugador1->colision_bullets(*plat, pantalla.W, pantalla.H);
            jugador2->colision_bullets(*plat, pantalla.W, pantalla.H);
            for (auto& e : vec_enemigos) {
                e->colision_platform(*plat);
                e->colision_bullets(*plat, pantalla.W, pantalla.H);
            }
            for (auto& t : vec_trampas)
                t->colision_platform_window(*plat, pantalla.W, pantalla.H);
            for (auto& i : vec_items)
                i->unlock_platform(*plat);        
        }

        for (auto& e : vec_enemigos)
        {
            e->Draw(App);
            e->update();
            e->move();
            e->colision_windows(pantalla.W, pantalla.H);
            e->attack(App);
            e->draw_bullets(App);
            e->colision_player_bullet(*jugador1, *jugador2);
            jugador1->colision_enemy(*e);
            jugador2->colision_enemy(*e);
        }

        for (auto e = vec_enemigos.begin(); e != vec_enemigos.end(); e++) {
            if (!(*e)->is_life()) {

                auto tipo_enemigo = (*e)->get_tipo_enemigo();

                if (tipo_enemigo == Enemy::TIPO_ENEMIGO::OVNI || tipo_enemigo == Enemy::TIPO_ENEMIGO::SUBMARINO || tipo_enemigo == Enemy::TIPO_ENEMIGO::THROWING_FIRE || tipo_enemigo == Enemy::TIPO_ENEMIGO::UNKNOW_BALL) {
                    enemigo_muerte_2.play_sound_dead();
                    enemigo_muerte_2.set_position((*e)->getPosition_x() - (*e)->get_sprite_size_x() / 2, (*e)->getPosition_y() - (*e)->get_sprite_size_y() / 2);
                    enemigo_muerte_2.set_scale((*e)->get_scale_x(), (*e)->get_scale_y());
                    enemigo_muerte_2.update();
                    enemigo_muerte_2.draw(App);
                }
                else {
                    enemigo_muerte_1.play_sound_dead();
                    enemigo_muerte_1.set_position((*e)->getPosition_x() - (*e)->get_sprite_size_x() / 2, (*e)->getPosition_y() - (*e)->get_sprite_size_y() / 2);
                    enemigo_muerte_1.set_scale((*e)->get_scale_x(), (*e)->get_scale_y());
                    enemigo_muerte_1.update();
                    enemigo_muerte_1.draw(App);
                }

                if ((*e)->get_tipo_enemigo() == Enemy::TIPO_ENEMIGO::UNKNOW_BALL) {
                    crear_alien = true;
                    pos_x = (*e)->getPosition_x();
                    pos_y = (*e)->getPosition_y();
                }

                if ((*e)->get_ultima_bala() == Enemy::ULTIMA_BALA::PLAYER_1) {
                    jugador1->puntaje.set_puntos_enemigos(jugador1->puntaje.get_puntos_enemigos() + (*e)->get_puntaje_enemigo());    
                    jugador1->puntaje.set_enemigos_asesinados(jugador1->puntaje.get_enemigos_asesinados() + 1);
                }
                else if ((*e)->get_ultima_bala() == Enemy::ULTIMA_BALA::PLAYER_2) {
                    jugador2->puntaje.set_puntos_enemigos(jugador2->puntaje.get_puntos_enemigos() + (*e)->get_puntaje_enemigo());
                    jugador2->puntaje.set_enemigos_asesinados(jugador2->puntaje.get_enemigos_asesinados() + 1);
                }
                delete (*e);
                vec_enemigos.erase(e);
                break;
            }
        }

        if (crear_alien) {
            Enemy* alien = new Alien;
            alien->initialize(pos_x, pos_y, 2.5f);
            alien->setScale(0.9f, 0.9f);
            vec_enemigos.push_back(alien);
        }
       
        for (auto& i : vec_items)
        {
            i->draw(App);
            i->update();
            i->effect(*jugador1);
            i->effect(*jugador2);
        }
        for (auto& t : vec_trampas)
        {
            t->draw(App);
            t->move();
            t->effect(*jugador1);
            t->effect(*jugador2);
            t->update();
        }
        jugador1->draw(App);
        jugador1->control();
        jugador1->attack();
        jugador1->update();
        jugador1->draw_bullets(App);
        jugador2->draw(App);
        jugador2->control();
        jugador2->attack();
        jugador2->update();
        jugador2->draw_bullets(App);

        App.display();
}

bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { return (a.second > b.second); }

bool detectar_portal(std::vector<Item*>& portal)
{
    for (const auto& i : portal) {
        if (i->recogido && i->tipo_item == Item::TIPO_ITEM::PORTAL)
            return true;
    }
    return false;
}

bool detectar_llave(std::vector<Item*>& llave)
{
    for (const auto& i : llave) {
        if (i->recogido && i->tipo_item == Item::TIPO_ITEM::KEY)
            return true;
    }
    return false;
}

void borrar_balas(Player& p1, Player& p2, std::vector<Enemy*>& enemigos)
{
    if (!p1.balas.empty()) {
        for (auto& b : p1.balas)
            delete b;
        p1.balas.clear();
    }
    if (!p2.balas.empty()) {
        for (auto& b : p2.balas)
            delete b;
        p2.balas.clear();
    }
    for (auto& e : enemigos)
    {
        if (!e->balas.empty())
            delete e;
        e->balas.clear();
    }
}

void borrar_objetos(std::vector<Item*>& items, std::vector<Traps*>& trampas, std::vector<Enemy*>& enemigo, std::vector<Platform*>& plataformas, std::vector<Platform*>& des_plataformas)
{
    if (!items.empty()) {
        for (auto& plt : items)
            delete plt;
        items.clear();
    }
    if (!trampas.empty()) {
        for (auto& plt : trampas)
            delete plt;
        trampas.clear();
    }
    if (!enemigo.empty()) {
        for (auto& e : enemigo)
            delete e;
        enemigo.clear();
    }
    if (!plataformas.empty()) {
        for (auto& i : plataformas)
            delete i;
        plataformas.clear();
    }
    if (!des_plataformas.empty()) {
        for (auto& t : des_plataformas)
            delete t;
        des_plataformas.clear();
    }
}

std::pair<std::string, int> mayor_puntaje_jugador(Player* p1, Player* p2) {

    if (p1->puntaje.getTotal() > p2->puntaje.getTotal()) {
        return std::make_pair("Jugador_1", p1->puntaje.getTotal());
    }
    else if (p1->puntaje.getTotal() < p2->puntaje.getTotal()) {
        return std::make_pair("Jugador_2", p2->puntaje.getTotal());
    }
    else {
        return std::make_pair("EMPATE", p1->puntaje.getTotal());
    }
}