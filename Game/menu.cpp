#include "menu.h"

Menu::Menu(){
	window = new sf::RenderWindow();
	winclose = new sf::RectangleShape();
	font = new sf::Font();
	image = new sf::Texture();
	bg = new sf::Sprite();
	
	set_values();
}

Menu::~Menu(){
	delete window;
	delete winclose;
	delete font;
	delete image;
	delete bg;
}
	
void Menu::set_values(){
	window->create(sf::VideoMode(1280,720), "Menu SFML", sf::Style::Titlebar | sf::Style::Close);
	window->setPosition(sf::Vector2i(0,0));
	
	pos = 0;
	pressed = theselect = false;
	font->loadFromFile("./data/menu/ethn.otf");
	
	image->loadFromFile("./data/menu/menu-game.png");
	bg->setTexture(*image);
	
	pos_mouse = {0,0};
	mouse_coord = {0, 0};
	
	options = {"Dimension Travelers", "Jugar", "Puntuaciones", "Controles", "Salir"};
	texts.resize(5);
	coords = {{400,30},{25,185},{25,270},{25,360},{25,443}};
	sizes = {30,28,24,24,24};
	
	for (std::size_t i{}; i < texts.size(); ++i){
		texts[i].setFont(*font); 
		texts[i].setString(options[i]); 
		texts[i].setCharacterSize(sizes[i]);
		texts[i].setOutlineColor(sf::Color::Black);
		texts[i].setPosition(coords[i]);
	}
	texts[1].setOutlineThickness(4);
	pos = 1;
	
	//PUNTUACIONES
	//Load hightscores (se cargarian de un archuvo externo)
	options = {"Puntuaciones","- Ply\t1000","- Ply\t1000","- Ply\t1000","- Ply\t1000","- Ply\t1000"}; //Por defecto
	scores.resize(6);
	coords = {{500,100},{520,150},{520,180},{520,210},{520,240},{520,270}};
	sizes = {28,24,24,24,24,24};
	
	for (std::size_t i{}; i < scores.size(); ++i){
		scores[i].setFont(*font); 
		scores[i].setString(options[i]); 
		scores[i].setCharacterSize(sizes[i]);
		scores[i].setOutlineColor(sf::Color::Black);
		scores[i].setPosition(coords[i]);
	}
	
	//Close Button 
	winclose->setSize(sf::Vector2f(23,26));
	winclose->setPosition(1178,39);
	winclose->setFillColor(sf::Color::Transparent);
}

void Menu::loop_events(){
	sf::Event event;
	while(window->pollEvent(event)){
		if( event.type == sf::Event::Closed){
			window->close();
		}
		
		pos_mouse = sf::Mouse::getPosition(*window);
		mouse_coord = window->mapPixelToCoords(pos_mouse);
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed){
			if( pos < 4){
				++pos;
				pressed = true;
				texts[pos].setOutlineThickness(4);
				texts[pos - 1].setOutlineThickness(0);
				pressed = false;
				theselect = false;
			}
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed){
			if( pos > 1){
				--pos;
				pressed = true;
				texts[pos].setOutlineThickness(4);
				texts[pos + 1].setOutlineThickness(0);
				pressed = false;
				theselect = false;
			}
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !theselect){
			theselect = true;
			if( pos == 1)std::cout << "JUGAR\n";//RUN GAME
			if( pos == 4)window->close();
		}
		
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if(winclose->getGlobalBounds().contains(mouse_coord)){
				window->close();
			}
		}
	}
}

void Menu::draw_all(){
	window->clear();
	window->draw(*bg);
	for(auto t : texts){
		window->draw(t); 
	}
	if(pos==2 && theselect){
		for(auto t : scores){
			window->draw(t); 
		}
	}
	if(pos==3 && theselect){
		image->loadFromFile("./data/menu/menu-controles.png");
		bg->setTexture(*image);
	}
	else{
		image->loadFromFile("./data/menu/menu-game.png");
		bg->setTexture(*image);
	}
	
	window->display();
}

void Menu::run_menu(){
	while(window->isOpen()){
		loop_events();
		draw_all();
	}
}
