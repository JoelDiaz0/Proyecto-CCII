#include "menu.h"

Menu::Menu(){
	winclose = new sf::RectangleShape();
	font = new sf::Font();
	image = new sf::Texture();
	bg = new sf::Sprite();
	set_values();
}

Menu::~Menu(){
	delete winclose;
	delete font;
	delete image;
	delete bg;
}
	
void Menu::set_values(){
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
	//Load hightscores (Archivo de datos del juego 'coming soon...')
	//Podria cargar los puntajes en un map (player, score)
	std::fstream userdata("userdata.txt"); //Extraer niveles desbloqueados y puntuaciones
	int lvl; //PERMISOS DE NIVEL "Niveles desbloqueados"
	if (userdata.is_open()) { 
		std::string tp;
		userdata >> lvl;
		while (std::getline(userdata, tp)) std::cout << tp << "\n"; 
		userdata.close(); 
	}
	//std::cout << lvl; Probando lectura de datos
	options = {"Ply\t0000","Ply\t0000","Ply\t0000","Ply\t0000","Ply\t0000"}; //Default
	scores.resize(5);
	std::pair<int, float> textData = std::make_pair(0, 250); //Index texto,cords en Y

	for (auto & i : scores){
		i.setFont(*font); 
		i.setString(options[textData.first]); 
		i.setCharacterSize(24);
		i.setOutlineColor(sf::Color::Black);
		i.setPosition({760,textData.second});
		textData.first ++;
		textData.second += 50;
	}

	//Niveles desbloqueados (Cargados del archivo 'userdata') 
	//Level buttons
	levels.resize(5);
	int c = 450;
	for (auto& i : levels) {
		i.setSize(sf::Vector2f(100, 100));
		i.setPosition(c, 300);
		i.setFillColor(sf::Color::Black);
		c += 150;
	}

	//Close Button 
	winclose->setSize(sf::Vector2f(23, 26));
	winclose->setPosition(1178, 39);
	winclose->setFillColor(sf::Color::Transparent);
}

void Menu::loop_events(sf::RenderWindow& window, int& level){
	sf::Event event;
	while(window.pollEvent(event)){
		if( event.type == sf::Event::Closed) window.close();
		
		pos_mouse = sf::Mouse::getPosition(window);
		mouse_coord = window.mapPixelToCoords(pos_mouse);
		
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
			if(pos == 4) window.close();
		}
		
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			if(winclose->getGlobalBounds().contains(mouse_coord)) window.close();
			//Level boxes interaction (Para jugar niveles del 1 al 5)
			if (pos == 1) {
				if (levels.at(0).getGlobalBounds().contains(mouse_coord)) level = 1;
				if (levels.at(1).getGlobalBounds().contains(mouse_coord)) level = 2;
				if (levels.at(2).getGlobalBounds().contains(mouse_coord)) level = 3;
				if (levels.at(3).getGlobalBounds().contains(mouse_coord)) level = 4;
				if (levels.at(4).getGlobalBounds().contains(mouse_coord)) level = 5;
			}
		}
	}
}

void Menu::draw_all(sf::RenderWindow& window){
	window.clear();
	window.draw(*bg);
	for(auto t : texts){
		window.draw(t); 
	}
	if (pos == 1) {
		for (auto l : levels) window.draw(l);
		image->loadFromFile("./data/menu/menu-game.png");
		bg->setTexture(*image);
	}
	if(pos == 2){
		for(auto t : scores) window.draw(t); 
		image->loadFromFile("./data/menu/menu-puntuaciones.png");
		bg->setTexture(*image);
	}
	if(pos == 3){
		image->loadFromFile("./data/menu/menu-controles.png");
		bg->setTexture(*image);
	}
	window.display();
}

void Menu::run_menu(sf::RenderWindow& window, int& level){
	while(window.isOpen() && level == 0){
		loop_events(window,level);
		draw_all(window);
	}
}
