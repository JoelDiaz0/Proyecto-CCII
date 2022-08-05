#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <vector>
#include <iostream>
#include "Demon.h"
#include "Throwingfire.h"
#include "Fungus.h"
#include "BloodMonster.h"
#include "Harpy.h"
#include "menu.h"
#include "Hell.h"
#include "Tatooine.h"
#include "montana.h"
#include "Muerte.h"
#include "Key.h"
#include "Portal.h"
#include "Puntos.h"
#include "Lava.h"
#include "Spike.h"
#include "Spike_Run.h"
#include "Spear.h"
#include "Suriken.h"
#include "Pendulum.h"
#include "Mallet.h"
#include "Fallen_Block.h"
#include "Platform_Movil.h"
using std::cout;
using std::endl;
struct window
{
     int W = 1280;
     int H = 720;
}pantalla;
bool cargando = true; //CARGAR ENEMIGOS Y PLATAFORMAS
int level = 0; //CAMBIO DE NIVEL
bool sortbysec(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b);//Comparador de pares de puntuacion
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

    //Musica - Level 1 
    sf::Music m1, m5;
    m1.openFromFile("data\\music\\music-level1.ogg");
    m1.setVolume(11.5f);
    //Musica - Level 5
    m5.openFromFile("data\\music\\the_hell.ogg");
    m5.setVolume(11.5f);

    //Cargando texturas y creando animaciones para las SONIDOS
    sf::SoundBuffer sonido_rayo, sonido_fuego1, sonido_danio, sonido_fuego2, sonido_bala, sonido_muerte, sonido_item, sonido_revivir, sonido_llave, sonido_portal;
    sonido_rayo.loadFromFile("data\\sound\\attack_thunder.ogg");
    sonido_fuego1.loadFromFile("data\\sound\\attack_fire_1.ogg");
    sonido_danio.loadFromFile("data\\sound\\damage.ogg");
    sonido_fuego2.loadFromFile("data\\sound\\FlameAtack.ogg");
    sonido_bala.loadFromFile("data\\sound\\bala_1.ogg");
    sonido_muerte.loadFromFile("data\\sound\\dead.ogg");
    sonido_item.loadFromFile("data\\sound\\score.ogg");
    sonido_revivir.loadFromFile("data\\sound\\revivir.ogg");
    sonido_llave.loadFromFile("data\\sound\\llave.ogg");
    sonido_portal.loadFromFile("data\\sound\\portal.ogg");

    //Fondo level 1 -------
    sf::Texture f1;
    f1.loadFromFile("data\\background\\tatooine_background.jpg");

    //VECTORES
    std::vector<Item*> vec_items;
    std::vector<Traps*> vec_trampas;
    std::vector<Enemy*> vec_enemigos; 
    std::vector<Platform*> vec_plataformas;
    std::vector<Platform*> vec_unlock_plataformas; //plataformas que se pueden eliminar al recoger la llave
    std::vector<sf::Texture> vec_textures; //Para Fondo Animado
    std::vector<sf::Sprite> vec_sprites; //Para Fondo Animado

    //Cargando texturas y creando animaciones para las ITEMS
    sf::Texture tex_item1, tex_item2, tex_item3, tex_portal, tex_key;
    tex_item1.loadFromFile("data\\sprites\\item_resucitar.png");
    tex_item2.loadFromFile("data\\sprites\\item_muerte.png");
    tex_item3.loadFromFile("data\\sprites\\item_puntos.png");
    tex_key.loadFromFile("data\\sprites\\llave.png");
    tex_portal.loadFromFile("data\\sprites\\portal.png");
    Animation item1, item2, item3, anim_portal, anim_key;
    item1.Initialize(tex_item1, 31, 57, 5, 0.085);
    item2.Initialize(tex_item2, 31, 57, 5, 0.085);
    item3.Initialize(tex_item3, 31, 57, 5, 0.085);
    anim_portal.Initialize(tex_portal, 50, 98, 7, 0.065);
    anim_key.Initialize(tex_key,35,100,2,0.15);

    //Cargando texturas y creando animaciones para las TRAMPAS
    sf::Texture tex_spike, tex_spike_run, tex_lava, tex_suriken, tex_mallet, tex_pendulum, tex_block, tex_spear;
    tex_spike.loadFromFile("data\\sprites\\spike.png");
    tex_spike_run.loadFromFile("data\\sprites\\spike_run.png");
    tex_lava.loadFromFile("data\\sprites\\lava.png");
    tex_suriken.loadFromFile("data\\sprites\\suriken.png");
    tex_mallet.loadFromFile("data\\sprites\\mazo.png");
    tex_pendulum.loadFromFile("data\\sprites\\pendulo.png");
    tex_block.loadFromFile("data\\sprites\\block.png");
    tex_spear.loadFromFile("data\\sprites\\Spear.png");
    Animation anim_spike, anim_spike_run, anim_lava, anim_suriken, anim_mallet, anim_pendulum, anim_spear;
    anim_spike.Initialize(tex_spike,32,14,10,0.075);
    anim_spike_run.Initialize(tex_spike_run, 31, 25, 4, 0.075);
    anim_lava.Initialize(tex_lava, 64, 13, 2, 0.08);
    anim_suriken.Initialize(tex_suriken, 32, 32, 8, 0.015);
    anim_mallet.Initialize(tex_mallet,102,300,2,0.1);
    anim_pendulum.Initialize(tex_pendulum,178,300,2,0.1);
    anim_spear.Initialize(tex_spear, 9, 64, 12, 0.055);
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
    p1_death.Initialize(t1_death, 38, 34, 5, 0.1);
    p1_jump.Initialize(t1_jump, 34, 35, 4, 0.075);
    p2_idle.Initialize(t2_idle, 20, 35, 4, 0.1);
    p2_run.Initialize(t2_run, 27, 34, 6, 0.075);
    p2_attack.Initialize(t2_attack, 28, 35, 6, 0.035);
    p2_up.Initialize(t2_up, 26, 36, 5, 0.075);
    p2_death.Initialize(t2_death, 38, 34, 6, 0.08);
    p2_jump.Initialize(t2_jump, 27, 36, 4, 0.075);

    //JUGADOR
    Player* jugador1 = new Player;
    Player* jugador2 = new Player;
    jugador1->Initialize_7(p1_idle, p1_run, p1_jump, p1_attack, p1_up, p1_death, b1, 50.f, pantalla.H - 150.f, 3.5f);
    jugador2->Initialize_7(p2_idle, p2_run, p2_jump, p2_attack, p2_up, p2_death, b2, 50.f, pantalla.H - 150.f, 3.5f);
    jugador1->setScale(2.5f, 2.5f);
    jugador2->setScale(2.5f, 2.5f);
    jugador1->cargar_audio_3(sonido_rayo, sonido_muerte, sonido_revivir);
    jugador2->cargar_audio_3(sonido_fuego1, sonido_muerte, sonido_revivir);

    //Cargando texturas para las PLATAFORMAS

    //PLATAFORMAS MOVILES
    sf::Texture tex_platMovil1, tex_platMovil2;
    tex_platMovil1.loadFromFile("data\\sprites\\MovingPlatfrom.png");
    tex_platMovil2.loadFromFile("data\\sprites\\FlyingPlatfrom.png");
    Animation anim_platMovil1, anim_platMovil2;
    anim_platMovil1.Initialize(tex_platMovil1,26,7,10,0.075);
    anim_platMovil2.Initialize(tex_platMovil2,30,11,8,0.055);

    //PLATAFORMAS ESTATICAS
    // level 1
    sf::Texture level_tatooine;
    level_tatooine.loadFromFile("data\\background\\tatooine_graphics.png");
    sf::Sprite fondo1;
    fondo1.setTexture(f1);

    // level 2 
    sf::Texture level_underwater;
    level_underwater.loadFromFile("./data/background/underwater-bg.png");
    sf::Sprite fondo2;
    fondo2.setTexture(level_underwater);

    //level 5


    //Textura level 5

    sf::Texture level_hell; 
    level_hell.loadFromFile("data\\background\\hell_graphics.png");
    //level 3 montana textura
    sf::Texture text_montana;
    text_montana.loadFromFile("data\\sprites\\nivel_3\\fondo.png");
    sf::Sprite level_montana(text_montana);
    level_montana.scale(sf::Vector2f(0.7f, 0.67f));
   //PISOS DEL NIVEL 3
    sf::Texture piso_montana;
    piso_montana.loadFromFile("data\\sprites\\nivel_3\\piso1.png");

    //Cargando texturas y creando animaciones para los ENEMIGOS
    sf::Texture tex_fungus, tex_bloodmonster, tex_demon_gun, tex_demon_walk, tex_throwigfire, tex_harpy;
    tex_demon_walk.loadFromFile("data\\sprites\\demon_walk.png");
    tex_demon_gun.loadFromFile("data\\sprites\\demon_attack.png");
    tex_fungus.loadFromFile("data\\sprites\\fungus.png");
    tex_throwigfire.loadFromFile("data\\sprites\\throwingfire.png");
    tex_bloodmonster.loadFromFile("data\\sprites\\bloodmonster.png");
    tex_harpy.loadFromFile("data\\sprites\\harpy.png");
    Animation anim_fungus, anim_bloodmonster, anim_demon_gun, anim_demon_walk, anim_throwigfire, anim_harpy;
    anim_demon_walk.Initialize(tex_demon_walk, 80, 109, 3, 0.2);
    anim_demon_gun.Initialize(tex_demon_gun, 122, 112, 2, 0.075);
    anim_fungus.Initialize(tex_fungus, 17, 20, 3, 0.055);
    anim_throwigfire.Initialize(tex_throwigfire, 39, 46, 1, 0.055);
    anim_bloodmonster.Initialize(tex_bloodmonster, 75, 31, 7, 0.075);
    anim_harpy.Initialize(tex_harpy,47,77,7,0.09);
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
       
        if (level == 0)
        { 
            Menu* menu = new Menu(puntuaciones);
            menu->run_menu(App,level);
            delete menu;
            menu = nullptr;
        }

        else if (level == 1)
        {
            if (cargando)
            {
                jugador1->setPosition(20.f, 0.f);
                jugador2->setPosition(10.f, 500.f);
                cout << "Cargando una vez elementos en level " << level << endl;
                m1.play();
                float xF1{ 0.2f }, yF1{ 0.2f }; //variables para la plateforma              
                //plat 1
                for (int i = 0; i < 2; i++)
                {
                    Platform* piso_plat1 = new Tatooine;
                    piso_plat1->initialize(level_tatooine);
                    piso_plat1->generar_bloque_1();
                    piso_plat1->setScale(xF1, yF1);
                    piso_plat1->setPosition(0 + (102.4f * i), 220.f);
                    vec_plataformas.push_back(piso_plat1);
                }
                Platform* piso_plat1a = new Tatooine;
                piso_plat1a->initialize(level_tatooine);
                piso_plat1a->generar_bloque_2();
                piso_plat1a->setScale(xF1, yF1);
                piso_plat1a->setPosition(204.8f, 220.f);
                vec_plataformas.push_back(piso_plat1a);

                //plat 2
                for (int i = 0; i < 2; i++)
                {
                    Platform* piso_plat2 = new Tatooine;
                    piso_plat2->initialize(level_tatooine);
                    piso_plat2->generar_bloque_1();
                    piso_plat2->setScale(xF1, yF1);
                    piso_plat2->setPosition(0 + (102.4f * i), 630.f);
                    vec_plataformas.push_back(piso_plat2);
                }
                Platform* piso_plat2a = new Tatooine;
                piso_plat2a->initialize(level_tatooine);
                piso_plat2a->generar_bloque_2();
                piso_plat2a->setScale(xF1, yF1);
                piso_plat2a->setPosition(204.8f, 650.f);
                vec_plataformas.push_back(piso_plat2a);
                //plat 3
                Platform* piso_plat3 = new Tatooine;
                piso_plat3->initialize(level_tatooine);
                piso_plat3->generar_bloque_4();
                piso_plat3->setScale(xF1, yF1);
                piso_plat3->setPosition(350, 580);
                vec_plataformas.push_back(piso_plat3);
                //plat 4
                Platform* piso_plat4 = new Tatooine;
                piso_plat4->initialize(level_tatooine);
                piso_plat4->generar_bloque_4();
                piso_plat4->setScale(xF1, yF1);
                piso_plat4->setPosition(440.f, 300.f);
                vec_plataformas.push_back(piso_plat4);
                //plat 5
                Platform* piso_plat5 = new Tatooine;
                piso_plat5->initialize(level_tatooine);
                piso_plat5->generar_bloque_3();
                piso_plat5->setScale(xF1, yF1);
                piso_plat5->setPosition(600.f, 500.f);
                vec_plataformas.push_back(piso_plat5);
                //plat 6
                Platform* piso_plat6 = new Tatooine;
                piso_plat6->initialize(level_tatooine);
                piso_plat6->generar_bloque_3();
                piso_plat6->setScale(xF1, yF1);
                piso_plat6->setPosition(790.f, 250.f);
                vec_plataformas.push_back(piso_plat6);
                //plat 7
                Platform* piso_plat7 = new Tatooine;
                piso_plat7->initialize(level_tatooine);
                piso_plat7->generar_bloque_3();
                piso_plat7->setScale(xF1, yF1);
                piso_plat7->setPosition(800.f, 400.f);
                vec_plataformas.push_back(piso_plat7);
                //plat 8
                Platform* piso_plat8 = new Tatooine;
                piso_plat8->initialize(level_tatooine);
                piso_plat8->generar_bloque_3();
                piso_plat8->setScale(xF1, yF1);
                piso_plat8->setPosition(790.f, 600.f);
                vec_plataformas.push_back(piso_plat8);
                //plat 9
                Platform* piso_plat9 = new Tatooine;
                piso_plat9->initialize(level_tatooine);
                piso_plat9->generar_bloque_3();
                piso_plat9->setScale(xF1, yF1);
                piso_plat9->setPosition(1090.f, 200.f);
                vec_plataformas.push_back(piso_plat9);
                //plat 10
                Platform* piso_plat10 = new Tatooine;
                piso_plat10->initialize(level_tatooine);
                piso_plat10->generar_bloque_3();
                piso_plat10->setScale(xF1, yF1);
                piso_plat10->setPosition(1080.f, 550.f);
                vec_plataformas.push_back(piso_plat10);
                //plat 11
                Platform* piso_plat11 = new Tatooine;
                piso_plat11->initialize(level_tatooine);
                piso_plat11->generar_bloque_4();
                piso_plat11->setScale(xF1, yF1);
                piso_plat11->setPosition(1080.f, 350.f);
                vec_plataformas.push_back(piso_plat11);
            }

            //DESARROLLO DEL NIVEL

            cargando = false;
            m1.setLoop(true);
            App.clear();
            App.draw(fondo1);
            jugador1->colision_windows(pantalla.W, pantalla.H);
            jugador2->colision_windows(pantalla.W, pantalla.H);

            for (auto plat : vec_plataformas)
            {
                plat->draw(App);
                jugador1->colision_platform(*plat);
                jugador2->colision_platform(*plat);
            }
            jugador1->draw_1(App);
            jugador1->Update();
            jugador1->attack_1(App);
            jugador1->draw_bullet(App);
            jugador2->draw_2(App);
            jugador2->Update();
            jugador2->attack_2(App);
            jugador2->draw_bullet(App);

            App.display();
        }

        else if (level == 2)
        {
            //KEVIN - FONDO DEL MAR 
            cargando = false;
            m1.setLoop(true);

            App.clear();
            App.draw(fondo2);

            jugador1->colision_windows(pantalla.W, pantalla.H);
            jugador2->colision_windows(pantalla.W, pantalla.H);

            jugador1->draw_1(App);
            jugador1->Update();
            jugador1->attack_1(App);
            jugador2->draw_2(App);
            jugador2->Update();
            jugador2->attack_2(App);

            App.display();
        }
        ////////NIVEL 3//////////////////////////////////
        else if (level == 3)
        {
            //DIEGO - MONTAÑA
             //CARGANDO PLATAFORMAS Y ENEMIGOS
            if (cargando){ 
                float xF1{ 1.2f }, yF1{ 1.2f };
                jugador1->setPosition(620.f,0.f);
                jugador2->setPosition(660.f,20.f);
                cout << "Cargando una vez elementos en level " << level << endl;
                m5.play();
                for (int i = 0; i < 8; i++)
                {
                    Platform* piso_montana1 = new montana;
                    piso_montana1->initialize(piso_montana);
                    piso_montana1->generar_bloque_1();
                    piso_montana1->setScale(xF1, yF1);
                    piso_montana1->setPosition(400.f + (58.f * i),120.f);
                    vec_plataformas.push_back(piso_montana1);
                }
   
            }

            //DESARROLLO DEL NIVEL
       
             cargando = false;
             m5.setLoop(true);

             App.clear();
             App.draw(level_montana);

             jugador1->colision_windows(pantalla.W, pantalla.H);
             jugador2->colision_windows(pantalla.W, pantalla.H);

             for (auto plat : vec_plataformas)
             {
                 plat->draw(App);
                 jugador1->colision_platform(*plat);
                 jugador2->colision_platform(*plat);
             }
             jugador1->draw_1(App);
             jugador1->Update();
             jugador1->attack_1(App);
             jugador1->draw_bullet(App);
             jugador2->draw_2(App);
             jugador2->Update();
             jugador2->attack_2(App);
             jugador2->draw_bullet(App);
             App.display();
        }
        
        else if (level == 4)
        {
            //AXEL - AMONGUS
        }
        
        else if (level == 5) //EL INFIERNO
        {
            //CARGANDO PLATAFORMAS Y ENEMIGOS
            if (cargando)
            {
                cout << "Cargando una vez elementos en level " << level << endl;
                m5.play();
                //Creando Plataformas
                for (int i = 0; i < 12; i++)
                {
                    Platform* Suelo = new Hell;
                    Suelo->initialize(level_hell);
                    Suelo->generar_bloque_1();
                    Suelo->setScale(2.f, 2.f);
                    Suelo->setPosition(i * 76.f * 2.f, pantalla.H - 33.f);
                    vec_plataformas.push_back(Suelo);
                    if (i < 2)
                        continue;
                    Platform* Plat2 = new Hell;
                    Plat2->initialize(level_hell);
                    Plat2->generar_bloque_2();
                    Plat2->setScale(2.f, 2.f);
                    Plat2->setPosition(i * 64.f * 2.f, 200.f);
                    vec_plataformas.push_back(Plat2);
                }
                //Creando Plataformas desbloqueables              
                for (int i = 0; i < 2; i++)
                {
                    Platform* Muro3 = new Hell;
                    Muro3->initialize(level_hell);
                    Muro3->generar_bloque_3();
                    Muro3->setScale(2.f, 2.f);
                    Muro3->setPosition(pantalla.W - 300.f, i*100.f);
                    vec_unlock_plataformas.push_back(Muro3);
                }          
                //Creando Plataforma Movil
                Traps* plataforma_movil2 = new Platform_Movil;
                plataforma_movil2->Inicialize(anim_platMovil2, 0.f, pantalla.H / 2.f, 0.f, 3.5f);
                plataforma_movil2->setScale(3.f, 3.f);
                vec_trampas.push_back(plataforma_movil2);
                //Creando Enemigos
                for (int i = 0; i < 1; i++)
                {
                   //Enemy* enemigo_demon = new Demon;
                   //enemigo_demon->Initialize_3(anim_demon_walk, anim_demon_gun, b4, pantalla.W - 200.f, pantalla.H - 200.f, 1.5f);
                   //enemigo_demon->setScale(1.5f, 1.5f);
                   //enemigo_demon->cargar_audio_2(sonido_danio,sonido_bala);
                   //vec_enemigos.push_back(enemigo_demon);
                    Enemy* enemigo_blodmonster = new BloodMonster;
                    enemigo_blodmonster->Initialize(anim_bloodmonster, 100.f, 0.f, 2.f);
                    enemigo_blodmonster->setScale(2.5f, 2.5f);
                    enemigo_blodmonster->cargar_audio(sonido_danio);
                    vec_enemigos.push_back(enemigo_blodmonster);
                    Enemy* enemigo_harpy = new Harpy;
                    enemigo_harpy->Initialize(anim_harpy, pantalla.W - 200.f, pantalla.H - 200.f, 2.5f);
                    enemigo_harpy->setScale(1.5f,1.5f);
                    enemigo_harpy->cargar_audio(sonido_danio);
                    vec_enemigos.push_back(enemigo_harpy);                                  
                }
                //Creando Items
                for (int i = 0; i < 1; i++)
                {
                    Item* item_puntos = new Puntos;
                    item_puntos->inicialize(item3, 300.f, pantalla.H-100.f);
                    item_puntos->setScale(0.85f, 0.85f);
                    item_puntos->setAudio(sonido_item);
                    vec_items.push_back(item_puntos);
                    Item* item_llave = new Key;
                    item_llave->inicialize(anim_key, pantalla.W/3.f, pantalla.H - 150.f);
                    item_llave->setScale(0.55f, 0.55f);
                    item_llave->setAudio(sonido_llave);
                    vec_items.push_back(item_llave);
                    Item* item_portal = new Portal;
                    item_portal->inicialize(anim_portal, pantalla.W - 100.f , 20.f);
                    item_portal->setScale(1.5f, 1.5f);
                    item_portal->setAudio(sonido_portal);               
                    vec_items.push_back(item_portal);          
                }
                //Creando Trampas
                for (int i = 0; i < 1; i++)
                {
                    Traps* trampa_spike = new Spike;
                    trampa_spike->Inicialize(anim_spike, pantalla.W / 2.f, pantalla.H - 60.f);
                    trampa_spike->setScale(2.5f,2.5f);
                    vec_trampas.push_back(trampa_spike);
                    Traps* trampa_spikerun = new Spike_Run;
                    trampa_spikerun->Inicialize(anim_spike_run, pantalla.W / 2.f, pantalla.H - 200.f,3.5f,0.f);
                    trampa_spikerun->setScale(2.5f, 2.5f); 
                    vec_trampas.push_back(trampa_spikerun);
                    Traps* trampa_spear = new Spear;
                    trampa_spear->Inicialize(anim_spear, pantalla.W - 100.f, pantalla.H - 180.f);
                    trampa_spear->setScale(2.5f, 2.5f);
                    vec_trampas.push_back(trampa_spear);
                    Traps* trampa_block = new Fallen_Block;
                    trampa_block->Inicialize(tex_block, pantalla.W / 2.f, pantalla.H / 2.f, 0.f, 4.5f);
                    trampa_block->setScale(0.5f, 0.5f);
                    vec_trampas.push_back(trampa_block);
                    Traps* trampa_mallet = new Mallet;
                    trampa_mallet->Inicialize(anim_mallet, pantalla.W / 2.f, pantalla.H / 2.f, 3.f, 0.f);
                    trampa_mallet->setScale(0.8f, 0.8f);
                    trampa_mallet->setOrigin(102/2.f,300/2.f);
                    vec_trampas.push_back(trampa_mallet);
                    Traps* trampa_pendulum = new Pendulum;
                    trampa_pendulum->Inicialize(anim_pendulum, pantalla.W - 100.f, pantalla.H / 2.f, 3.f, 0.f);
                    trampa_pendulum->setScale(0.8f, 0.8f);
                    trampa_pendulum->setOrigin(178 / 2.f, 0.f);
                    vec_trampas.push_back(trampa_pendulum);                                                           
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
                    s1.setScale(sf::Vector2f(1.75f, 2.f));
                    vec_sprites.push_back(s1);
                }
            }
            //DESARROLLO DEL NIVEL
            for (const auto &sp : vec_sprites)
            {
                cargando = false;
                m5.setLoop(true);
                App.clear();
                App.draw(sp);
                jugador1->colision_windows(pantalla.W, pantalla.H);
                jugador2->colision_windows(pantalla.W, pantalla.H);
                for (auto &plat : vec_plataformas)
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
                    for (auto& e : vec_enemigos)
                        e->colision_platform(*plat);
                    for (auto& t : vec_trampas)                    
                        t->colision_platform_window(*plat, pantalla.W, pantalla.H);
                    for (auto& i : vec_items)
                        i->unlock_platform(*plat);
                }
                for (auto &e : vec_enemigos)
                {
                    e->Draw(App);
                    e->Update();
                    e->move();
                    e->colision_windows(pantalla.W, pantalla.H);
                    e->attack(App);
                    e->draw_bullet(App);
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
                jugador1->draw_1(App);
                jugador1->Update();
                jugador1->attack_1(App);
                jugador1->draw_bullet(App);
                jugador2->draw_2(App);
                jugador2->Update();
                jugador2->attack_2(App);
                jugador2->draw_bullet(App);
                jugador1->resusitar(0.f,0.f);
                jugador2->resusitar(0.f,0.f);
                App.display();
            }
        }

        else if (level == 6)
        {
            //ALEX
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

    //ELIMINAR OBJETOS Y LIBERAR MEMORIA
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
   
    std::sort(puntuaciones.begin(), puntuaciones.end(),sortbysec);
    puntuaciones.resize(5);

    for (auto i : puntuaciones) cout << i.first << " " << i.second << endl;

    //Escribir los datos
    userdata.open("userdata.txt");
    if (userdata.is_open()){
        userdata << maxUnlockedLevel <<"\n";
        for(auto i:puntuaciones) userdata << i.first << " " << i.second << "\n";
        userdata.close();
    }
    

    for (auto &plt : vec_plataformas)
        delete plt;
    for (auto& plt : vec_unlock_plataformas)
        delete plt;
    for (auto &e : vec_enemigos)
        delete e;
    for (auto& i : vec_items)
        delete i;
    for (auto& t : vec_trampas)
        delete t;
    delete jugador1, jugador2;
    return 0;
}

bool sortbysec(const std::pair<std::string, int>& a,const std::pair<std::string, int>& b){return (a.second > b.second);}