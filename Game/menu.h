#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

class Menu {
	int pos;
	bool pressed, theselect;
	
	//Boxes
	sf::RectangleShape* winclose;
	std::vector<sf::RectangleShape> levels;

	sf::Font * font;
	sf::Texture * image;
	sf::Sprite * bg;
	
	sf::Vector2i pos_mouse;
	sf::Vector2f mouse_coord;
	
	std::vector<const char *> options;
	std::vector<sf::Vector2f> coords;
	std::vector<sf::Text> texts;
	std::vector<std::size_t> sizes;
	
	std::vector<sf::Text> scores;
	
protected:
	void set_values();
	void loop_events(sf::RenderWindow& window, int& level);
	void draw_all(sf::RenderWindow& window);
public:
	Menu();
	~Menu();
	void run_menu(sf::RenderWindow& window, int & level);
};
