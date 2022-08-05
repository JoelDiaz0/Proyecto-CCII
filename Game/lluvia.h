#include <SFML/Graphics.hpp>
#include <iostream>
class lluvia
{
public:
	void set_lluvia();
	void set_lluvia(int a);
	void posicion_scale(float a, float b);
	void movimiento();
	void movimiento(float a, float b);
	void dibujar(sf::RenderWindow& app);

private:
	sf::RectangleShape lluvia_cont;
	sf::Texture F_lluvia;
	float velx = 2;
	float vely = 5;
};