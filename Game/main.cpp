#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <vector>
#include <iostream>
#include <deque>
#include <list>
#include <memory>
#include "menu.h"
//Enemigos
#include "Demon.h"
#include "Throwingfire.h"
#include "Fungus.h"
#include "BloodMonster.h"
#include "Harpy.h"
//Plataformas por Nivel
#include "Hell.h"
#include "Tatooine.h"
#include "montana.h"
#include "montana2.h"
#include "SpaceSus.h"
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
//Escenarios (Patron de diseño builder)
#include "SceneryDirector.h"
#include "Scenery_Tatooine.h"
#include "Scenery_Hell.h"
#include "Scenary_LLuvia.h"
#include "Scenery_Space.h"
//Otros
#include "Excepcion.h"
#include "lluvia.h"
#include "Punk_1.h"
#include "Punk_2.h"
using std::cout;
using std::endl;

struct window
{
    int W = 1280;
    int H = 720;
}pantalla;


bool CARGANDO = true; //CARGAR ENEMIGOS Y PLATAFORMAS
int LEVEL = 0; //CAMBIO DE NIVEL

template<typename T>
void llamar(std::deque < std::shared_ptr<lluvia>> clases, sf::RenderWindow& app);
template<typename T>
void llamar(std::deque < std::shared_ptr<lluvia>> clases, sf::RenderWindow& app, int a);

bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);//Comparador de pares de puntuacion
bool detectar_portal(std::vector<Item*>& portal);
bool detectar_llave(std::vector<Item*>& llave);
void borrar_balas(Player& p1, Player& p2, std::vector<Enemy*>& enemigos);
void borrar_objetos(std::vector<Item*>& items, std::vector<Traps*>& trampas, std::vector<Enemy*>& enemigo, std::vector<Platform*>& plataformas, std::vector<Platform*>& des_plataformas);

int main()
{
    sf::RenderWindow App(sf::VideoMode(pantalla.W, pantalla.H, 32), "Juego");
    App.setFramerateLimit(60);
    bool fullscream = false;

    //PUNTUACIONES
    std::fstream userdata("userdata.txt"); //Extraer niveles desbloqueados y puntuaciones
    int maxUnlockedLevel{}; //PERMISOS DE NIVEL "Niveles desbloqueados"
    std::vector<std::pair<std::string, int>> puntuaciones;
    puntuaciones.resize(5);
    if (userdata.is_open()) {
        std::string tp;
        userdata >> maxUnlockedLevel;
        for (auto& i : puntuaciones) userdata >> i.first >> i.second;
        userdata.close();
    }

    //Contenedores
    std::vector<Item*> vec_items;
    std::vector<Traps*> vec_trampas;
    std::vector<Enemy*> vec_enemigos;
    std::vector<Platform*> vec_plataformas;
    std::vector<Platform*> vec_unlock_plataformas; //plataformas que se pueden eliminar al recoger la llave

    std::deque< std::shared_ptr<lluvia>> lluvias;
    std::deque< std::shared_ptr<lluvia>> lluvias_Acidas;


    //JUGADOR
    Player* jugador1 = new Punk_1();
    Player* jugador2 = new Punk_2();
    jugador1->initialize(50.f, pantalla.H - 150.f, 3.5f, 3.5f);
    jugador1->setScale(2.5f, 2.5f);
    jugador2->initialize(50.f, pantalla.H - 150.f, 3.5f, 3.5f);
    jugador2->setScale(2.5f, 2.5f);

    sf::Clock tiempo_spawn, tiempo_spawn_2;
    bool una_vez = false;

    //LLUVIA DEL NIVEL 3

    SceneryDirector* escenario = new SceneryDirector; //Patron Builder
    SceneryBuilder* escenario_infierno = new Scenery_Hell;
    SceneryBuilder* escenario_tatooine = new Scenery_Tatooine;
    SceneryBuilder* escenario_montana = new Scenary_Lluvia;
    SceneryBuilder* escenario_space = new Scenery_Space;

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
                Menu* menu = new Menu(puntuaciones);
                menu->run_menu(App, LEVEL);
                delete menu;
                menu = nullptr;
            }
            else if (LEVEL == 1) {
                if (CARGANDO) {
                    cout << "Cargando una vez elementos en level " << LEVEL << endl;
                    jugador1->setPosition(20.f, 0.f);
                    jugador2->setPosition(10.f, 500.f);
                    float xF1{ 0.2f }, yF1{ 0.2f }; //variables para la plateforma
                    //Creacion de Plataforma
                    //plat 1
                    for (int i = 0; i < 2; i++)
                    {
                        Platform* piso_plat1 = new Tatooine;
                        piso_plat1->initialize();
                        piso_plat1->generar_bloque_1();
                        piso_plat1->setScale(xF1, yF1);
                        piso_plat1->setPosition(0 + (102.4f * i), 220.f);
                        vec_plataformas.push_back(piso_plat1);
                    }
                    Platform* piso_plat1a = new Tatooine;
                    piso_plat1a->initialize();
                    piso_plat1a->generar_bloque_2();
                    piso_plat1a->setScale(xF1, yF1);
                    piso_plat1a->setPosition(204.8f, 220.f);
                    vec_plataformas.push_back(piso_plat1a);

                    //plat 2
                    for (int i = 0; i < 2; i++)
                    {
                        Platform* piso_plat2 = new Tatooine;
                        piso_plat2->initialize();
                        piso_plat2->generar_bloque_1();
                        piso_plat2->setScale(xF1, yF1);
                        piso_plat2->setPosition(0 + (102.4f * i), 630.f);
                        vec_plataformas.push_back(piso_plat2);
                    }
                    Platform* piso_plat2a = new Tatooine;
                    piso_plat2a->initialize();
                    piso_plat2a->generar_bloque_2();
                    piso_plat2a->setScale(xF1, yF1);
                    piso_plat2a->setPosition(204.8f, 650.f);
                    vec_plataformas.push_back(piso_plat2a);
                    //plat 3
                    Platform* piso_plat3 = new Tatooine;
                    piso_plat3->initialize();
                    piso_plat3->generar_bloque_4();
                    piso_plat3->setScale(xF1, yF1);
                    piso_plat3->setPosition(350, 580);
                    vec_plataformas.push_back(piso_plat3);
                    //plat 4
                    Platform* piso_plat4 = new Tatooine;
                    piso_plat4->initialize();
                    piso_plat4->generar_bloque_4();
                    piso_plat4->setScale(xF1, yF1);
                    piso_plat4->setPosition(440.f, 300.f);
                    vec_plataformas.push_back(piso_plat4);
                    //plat 5
                    Platform* piso_plat5 = new Tatooine;
                    piso_plat5->initialize();
                    piso_plat5->generar_bloque_3();
                    piso_plat5->setScale(xF1, yF1);
                    piso_plat5->setPosition(600.f, 500.f);
                    vec_plataformas.push_back(piso_plat5);
                    //plat 6
                    Platform* piso_plat6 = new Tatooine;
                    piso_plat6->initialize();
                    piso_plat6->generar_bloque_3();
                    piso_plat6->setScale(xF1, yF1);
                    piso_plat6->setPosition(790.f, 250.f);
                    vec_plataformas.push_back(piso_plat6);
                    //plat 7
                    Platform* piso_plat7 = new Tatooine;
                    piso_plat7->initialize();
                    piso_plat7->generar_bloque_3();
                    piso_plat7->setScale(xF1, yF1);
                    piso_plat7->setPosition(800.f, 400.f);
                    vec_plataformas.push_back(piso_plat7);
                    //plat 8
                    Platform* piso_plat8 = new Tatooine;
                    piso_plat8->initialize();
                    piso_plat8->generar_bloque_3();
                    piso_plat8->setScale(xF1, yF1);
                    piso_plat8->setPosition(790.f, 600.f);
                    vec_plataformas.push_back(piso_plat8);
                    //plat 9
                    Platform* piso_plat9 = new Tatooine;
                    piso_plat9->initialize();
                    piso_plat9->generar_bloque_3();
                    piso_plat9->setScale(xF1, yF1);
                    piso_plat9->setPosition(1090.f, 200.f);
                    vec_plataformas.push_back(piso_plat9);
                    //plat 10
                    Platform* piso_plat10 = new Tatooine;
                    piso_plat10->initialize();
                    piso_plat10->generar_bloque_3();
                    piso_plat10->setScale(xF1, yF1);
                    piso_plat10->setPosition(1080.f, 550.f);
                    vec_plataformas.push_back(piso_plat10);
                    //plat 11
                    Platform* piso_plat11 = new Tatooine;
                    piso_plat11->initialize();
                    piso_plat11->generar_bloque_4();
                    piso_plat11->setScale(xF1, yF1);
                    piso_plat11->setPosition(1080.f, 350.f);
                    vec_plataformas.push_back(piso_plat11);
                    //Portal
                    Item* item_portal2 = new Portal;
                    item_portal2->inicialize(pantalla.W - 100.f, 400.f);
                    item_portal2->setScale(1.5f, 1.5f);
                    vec_items.push_back(item_portal2);
                    //pinchos
                    Traps* trampa_spike = new Spike;
                    trampa_spike->Inicialize(80, 80);
                    trampa_spike->setScale(2.5f, 2.5f);
                    vec_trampas.push_back(trampa_spike);
                    Traps* trampa_pinchos(trampa_spike); //Constructor Copia
                    trampa_pinchos->Inicialize(990, 720);
                    //---------
                    escenario->setBuilder(escenario_tatooine);
                    escenario->construir_Scenary();
                    CARGANDO = false;
                }
                else {
                    App.clear();
                    escenario->draw_scenary(App);
                    escenario->reproducir_musica();
                    jugador1->colision_windows(pantalla.W, pantalla.H);
                    jugador2->colision_windows(pantalla.W, pantalla.H);

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
                        e->colision_player_bullet(*jugador1);
                        e->colision_player_bullet(*jugador2);
                        jugador1->colision_enemy(*e);
                        jugador2->colision_enemy(*e);
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
                    jugador1->revivir(0.f, 0.f);
                    jugador2->draw(App);
                    jugador2->control();
                    jugador2->attack();
                    jugador2->update();
                    jugador2->draw_bullets(App);
                    jugador2->revivir(0.f, 0.f);

                    if (detectar_portal(vec_items)) {
                        LEVEL = 3;
                        borrar_balas(*jugador1, *jugador2, vec_enemigos);
                        borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
                        escenario->parar_musica();
                        CARGANDO = true;
                    }

                    App.display();
                }
            }
            else if (LEVEL == 2) {


            }
            else if (LEVEL == 3) {
                if (CARGANDO) {
                    cout << "Cargando una vez elementos en level " << LEVEL << endl;
                    float xF1{ 1.2f }, yF1{ 1.2f };
                    jugador1->setPosition(620.0f, 0.0f);
                    jugador2->setPosition(660.0f, 0.0f);
                    escenario->setBuilder(escenario_montana);
                    escenario->construir_Scenary();

                    for (int i = 0; i < 40; i++) {                   
                        //lluvia* ll1 = new lluvia();
                        std::shared_ptr<lluvia> ll1 = std::make_shared<lluvia>();
                        ll1->set_lluvia();
                        ll1->posicion_scale(3, 3);
                        lluvias.push_back(ll1);
                    }
                    for (int i = 0; i < 40; i++) {
                        //lluvia* ll1 = new lluvia();
                        std::shared_ptr<lluvia> ll1 = std::make_shared<lluvia>();
                        ll1->set_lluvia(1);
                        ll1->posicion_scale(3, 3);
                        lluvias_Acidas.push_back(ll1);
                    }

                    for (int i = 0; i < 4; i++)
                    {
                        Platform* piso_plat1 = new montana;
                        //std::shared_ptr<Platform> piso_plat1 = std::make_shared<montana>();
                        piso_plat1->initialize();
                        piso_plat1->generar_bloque_1();
                        piso_plat1->setScale(xF1, yF1);
                        piso_plat1->setPosition(552 + (58 * i), 100);
                        vec_plataformas.push_back(piso_plat1);
                    }
                    for (int i = 0; i < 8; i++)
                    {
                        Platform* piso_plat_2 = new montana;
                        //std::shared_ptr<Platform> piso_plat_2 = std::make_shared<montana2>();
                        piso_plat_2->initialize();
                        piso_plat_2->generar_bloque_1();
                        piso_plat_2->setScale(xF1, yF1);
                        piso_plat_2->setPosition(0 + (58 * i), 250);
                        vec_plataformas.push_back(piso_plat_2);
                    }
                    for (int i = 0; i < 8; i++)
                    {
                        Platform* piso_plat_2 = new montana;
                        //std::shared_ptr<Platform> piso_plat_2 = std::make_shared<montana2>();
                        piso_plat_2->initialize();
                        piso_plat_2->generar_bloque_1();
                        piso_plat_2->setScale(xF1, yF1);
                        piso_plat_2->setPosition(1270 - (58 * i), 250);
                        vec_plataformas.push_back(piso_plat_2);
                    }
                    for (int i = 0; i < 4; i++)
                    {
                        Platform* piso_plat1 = new montana;
                        //std::shared_ptr<Platform> piso_plat1 = std::make_shared<montana>();
                        piso_plat1->initialize();
                        piso_plat1->generar_bloque_1();
                        piso_plat1->setScale(xF1, yF1);
                        piso_plat1->setPosition(552 + (58 * i), 450);
                        vec_plataformas.push_back(piso_plat1);
                    }
                    for (int i = 0; i < 26; i++)
                    {
                        Platform* piso_plat_2 = new montana;
                        //std::shared_ptr<Platform> piso_plat_2 = std::make_shared<montana2>();
                        piso_plat_2->initialize();
                        piso_plat_2->generar_bloque_1();
                        piso_plat_2->setScale(xF1, yF1);
                        piso_plat_2->setPosition(0 + (58 * i), 700);
                        vec_plataformas.push_back(piso_plat_2);
                    }
                    for (int i = 0; i < 6; i++)
                    {
                        Platform* piso_plat_2 = new montana;
                        //std::shared_ptr<Platform> piso_plat_2 = std::make_shared<montana2>();
                        piso_plat_2->initialize();
                        piso_plat_2->generar_bloque_1();
                        piso_plat_2->setScale(xF1, yF1);
                        piso_plat_2->setPosition(0 + (58 * i), 550);
                        vec_plataformas.push_back(piso_plat_2);
                    }
                    for (int i = 0; i < 6; i++)
                    {
                        Platform* piso_plat_2 = new montana;
                        //std::shared_ptr<Platform> piso_plat_2 = std::make_shared<montana2>();
                        piso_plat_2->initialize();
                        piso_plat_2->generar_bloque_1();
                        piso_plat_2->setScale(xF1, yF1);
                        piso_plat_2->setPosition(1270 - (58 * i), 550);
                        vec_plataformas.push_back(piso_plat_2);
                    }
                    //TRAMPA
                    Traps* trampa_spikerun = new Spike_Run;
                    trampa_spikerun->Inicialize(pantalla.W / 2.f, pantalla.H - 200.f, 10.0f, 0.f);
                    trampa_spikerun->setScale(2.5f, 2.5f);
                    vec_trampas.push_back(trampa_spikerun);
                    //ENEMIGO
                    Enemy* enemigo_blodmonster = new BloodMonster;

                    enemigo_blodmonster->initialize(0.f, 200.f, 2.f);
                    enemigo_blodmonster->setScale(2.5f, 2.5f);
              
                    vec_enemigos.push_back(enemigo_blodmonster);
                    for (int i = 0; i < 2; i++) {
                        Enemy* enemigo_harpy = new Harpy;
                        enemigo_harpy->initialize(1100 * i, 200, 2.5f);
                        enemigo_harpy->setScale(1.5f, 1.5f);
                        vec_enemigos.push_back(enemigo_harpy);
                    }
                    //PORTAL
                    Item* item_portal = new Portal;
                    item_portal->inicialize(1200, 600);
                    item_portal->setScale(1.5f, 1.5f);
                    vec_items.push_back(item_portal);
                    CARGANDO = false;
                }
                else {
                    App.clear();

                    escenario->draw_scenary(App);
                    escenario->reproducir_musica();

                    jugador1->colision_windows(pantalla.W, pantalla.H);
                    jugador2->colision_windows(pantalla.W, pantalla.H);
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
                    for (auto& plat : vec_plataformas)
                    {
                        plat->draw(App);
                        jugador1->colision_platform(*plat);
                        jugador2->colision_platform(*plat);
                        for (auto& e : vec_enemigos)
                            e->colision_platform(*plat);
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
                        e->colision_player_bullet(*jugador1);
                        e->colision_player_bullet(*jugador2);
                        jugador1->colision_enemy(*e);
                        jugador2->colision_enemy(*e);
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
                    jugador1->revivir(620.f, 0.f);
                    jugador2->draw(App);
                    jugador2->control();
                    jugador2->attack();
                    jugador2->update();
                    jugador2->draw_bullets(App);
                    jugador2->revivir(660.f, 0.f);

                    llamar<lluvia>(lluvias, App);
                    llamar<lluvia>(lluvias_Acidas, App, 1);

                    if (detectar_portal(vec_items)) {
                        LEVEL = 4;
                        escenario->parar_musica();
                        borrar_balas(*jugador1, *jugador2, vec_enemigos);
                        borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
                        CARGANDO = true;
                    }
                    App.display();
                }
            }
            else if (LEVEL == 4) {
                if (CARGANDO) {
                    //AXEL - AMONGUS             
                    //level 4               
                    jugador1->setPosition(520, 400);
                    jugador2->setPosition(700, 400);
                    //Creación de plataformas estáticas
                    for (int i = 0; i < 16; i++) {
                        Platform* Suelo = new SpaceSus;
                        Suelo->initialize();
                        Suelo->generar_bloque_3();
                        Suelo->setScale(1.8, 1.5);
                        Suelo->setPosition(160 + i * 60, 557);
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

                    //Plataformas extras para el spawn
                    Platform* SueloExtra = new SpaceSus;
                    SueloExtra->initialize();
                    SueloExtra->generar_bloque_4();
                    SueloExtra->setScale(4, 1.5);
                    SueloExtra->setPosition(20, 557);
                    vec_plataformas.push_back(SueloExtra);

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

                    //600 150
                    //Portal END
                    Item* item_portal = new Portal;
                    item_portal->inicialize(600, 0);
                    item_portal->setScale(1.5f, 1.5f);
                    vec_items.push_back(item_portal);

                    //Enemigos

                    Enemy* enemigo_harpy = new Harpy;
                    enemigo_harpy->initialize(0, 230, 2.5f);
                    enemigo_harpy->setScale(1.5f, 1.5f);
                    vec_enemigos.push_back(enemigo_harpy);
                    Enemy* enemigo_harpy2 = new Harpy;
                    enemigo_harpy2->initialize(900, 230, 2.5f);
                    enemigo_harpy2->setScale(1.5f, 1.5f);
                    vec_enemigos.push_back(enemigo_harpy2);
                    //2 enemigos eliminados para evitar dificultad innecesaria
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

                    for (auto& plat : vec_plataformas)
                    {
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
                        e->colision_player_bullet(*jugador1);
                        e->colision_player_bullet(*jugador2);
                        jugador1->colision_enemy(*e);
                        jugador2->colision_enemy(*e);
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
                    jugador1->revivir(0.f, 0.f);
                    jugador2->draw(App);
                    jugador2->control();
                    jugador2->attack();
                    jugador2->update();
                    jugador2->draw_bullets(App);
                    jugador2->revivir(0.f, 0.f);

                    App.display();

                    if (detectar_portal(vec_items)) {
                        LEVEL = 5;
                        escenario->parar_musica();
                        borrar_balas(*jugador1, *jugador2, vec_enemigos);
                        borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
                        CARGANDO = true;
                    }
                }
            }
            else if (LEVEL == 5) {
                if (CARGANDO) {
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

                        if (i % 3 != 0 && i < 4)
                        {
                            Item* item_muerte = new Muerte;
                            item_muerte->inicialize(200.f + i * i * 95.f * 2.0f, pantalla.H - 580.f);
                            item_muerte->setScale(0.85f, 0.85f);
                            vec_items.push_back(item_muerte);
                        }

                    }
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
                        e->colision_player_bullet(*jugador1);
                        e->colision_player_bullet(*jugador2);
                        jugador1->colision_enemy(*e);
                        jugador2->colision_enemy(*e);
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

                    if (detectar_llave(vec_items)) {
                        jugador1->revivir(pantalla.W - 50.f, 100.f);
                        jugador2->revivir(pantalla.W - 50.f, 100.f);
                        if (!una_vez) {
                            Enemy* enemigo_demon = new Demon;
                            enemigo_demon->initialize(300.f, pantalla.H - 550.f, 1.5f);
                            enemigo_demon->setScale(1.75f, 1.75f);
                            vec_enemigos.push_back(enemigo_demon);
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
                        LEVEL = 0;
                        escenario->parar_musica();
                        borrar_balas(*jugador1, *jugador2, vec_enemigos);
                        borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);
                        CARGANDO = true;
                    }
                    App.display();
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

    //Puntuaciones
    cout << "Jugador1:\n";
    cout << jugador1->puntaje << endl;
    cout << "Jugador2:\n";
    cout << jugador2->puntaje << endl;

    if (jugador1->puntaje > jugador2->puntaje)
        cout << "Jugador1 tiene el mayor puntaje\n";
    else if (jugador1->puntaje == jugador2->puntaje)
        cout << "Jugador1 y Jugador2 tienen el mismo puntaje\n";
    else
        cout << "Jugador2 tienen el mayor puntaje\n";

    //Puntuaciones escritura en el archivo 'userdata.txt'
    long p1_score = jugador1->puntaje.getTotal();
    long p2_score = jugador2->puntaje.getTotal();
    std::string pName{};
    puntuaciones.resize(7);
    if (p1_score > puntuaciones.back().second) {
        cout << "Nombre jugador 1: "; std::cin >> pName;
        puntuaciones.push_back(std::make_pair(pName, p1_score));
    }
    if (p2_score > puntuaciones.back().second) {
        cout << "Nombre jugador 2: "; std::cin >> pName;
        puntuaciones.push_back(std::make_pair(pName, p2_score));
    }

    std::sort(puntuaciones.begin(), puntuaciones.end(), sortbysec);
    puntuaciones.resize(5);

    for (auto& i : puntuaciones) cout << i.first << " " << i.second << endl;

    //Escribir los datos
    userdata.open("userdata.txt");
    if (userdata.is_open()) {
        userdata << maxUnlockedLevel << "\n";
        for (auto i : puntuaciones) userdata << i.first << " " << i.second << "\n";
        userdata.close();
    }

    //ELIMINAR OBJETOS Y LIBERAR MEMORIA
    borrar_objetos(vec_items, vec_trampas, vec_enemigos, vec_plataformas, vec_unlock_plataformas);

    if (vec_enemigos.empty()) {
        cout << "Vector vacio\n";
    }
    else {
        cout << "Vector lleno\n";
    }

    delete jugador1, jugador2, escenario, escenario_infierno, escenario_montana, escenario_tatooine, escenario_space;
    return 0;
}

bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { return (a.second > b.second); }

bool detectar_portal(std::vector<Item*>& portal)
{
    for (const auto& i : portal) {
        if (i->recogido && i->nombre == "portal")
            return true;
    }
    return false;
}

bool detectar_llave(std::vector<Item*>& llave)
{
    for (const auto& i : llave) {
        if (i->recogido && i->nombre == "key")
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
    cout << "Se borro balas\n";
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
    cout << "Se borro objetos\n";
}

template<typename T>
void llamar(std::deque < std::shared_ptr<lluvia>> clases, sf::RenderWindow& app) {
    for (auto llu : clases) {
        llu->movimiento();
        llu->dibujar(app);
    }
}
template<typename T>
void llamar(std::deque < std::shared_ptr<lluvia>> clases, sf::RenderWindow& app, int a) {
    for (auto llu : clases) {
        llu->movimiento(4.0f, 8.0f);
        llu->dibujar(app);
    }
}