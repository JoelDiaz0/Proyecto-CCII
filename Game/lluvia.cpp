#include "lluvia.h"
#include <random>
void lluvia::set_lluvia()
{
	F_lluvia.loadFromFile("data\\sprites\\nivel_3\\lluvia.png");
	lluvia_cont.setTexture(&F_lluvia);
	lluvia_cont.setSize(sf::Vector2f(5.0f, 12.0f));
	sf::Vector2u tamano = F_lluvia.getSize();
	lluvia_cont.setTextureRect(sf::IntRect(tamano.x * 0, tamano.y * 0, 16, 16));

}
void lluvia::set_lluvia(int a) {
	F_lluvia.loadFromFile("data\\sprites\\nivel_3\\lluvia1.png");
	lluvia_cont.setTexture(&F_lluvia);
	lluvia_cont.setSize(sf::Vector2f(5.0f, 12.0f));
	sf::Vector2u tamano = F_lluvia.getSize();
	lluvia_cont.setTextureRect(sf::IntRect(tamano.x * 0, tamano.y * 0, 16, 16));
}
void lluvia::posicion_scale(float a, float b) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(1.0, 1280);
	std::uniform_real_distribution<float> dist1(-400.5, -20);
	lluvia_cont.setPosition(dist(mt), dist1(mt));
	lluvia_cont.setScale(a, b);
}
void lluvia::movimiento()
{
	sf::Vector2f pos(lluvia_cont.getPosition().x, lluvia_cont.getPosition().y);
	pos.x -= velx;
	pos.y += vely;
	//std::cout <<"POSICION :"<< pos.x << "; " << pos.y << " \n";
	lluvia_cont.setPosition(pos);
	//std::cout << "vel :" << velx << "; " << vely << " \n";
	if (pos.y > 600 or pos.x < 0) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(1.0, 1300.0);
		pos.x = dist(mt);
		pos.y = 0;
		lluvia_cont.setPosition(pos);
	}

}

void lluvia::movimiento(float a, float b)
{
	sf::Vector2f pos(lluvia_cont.getPosition().x, lluvia_cont.getPosition().y);
	pos.x -= a;
	pos.y += b;
	//std::cout <<"POSICION :"<< pos.x << "; " << pos.y << " \n";
	lluvia_cont.setPosition(pos);
	velx++; vely++;
	//std::cout << "vel :" << velx << "; " << vely << " \n";
	if (pos.y > 600) {
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<float> dist(1.0, 1300.0);
		pos.x = dist(mt);
		pos.y = 0;
		lluvia_cont.setPosition(pos);
	}
}

void lluvia::dibujar(sf::RenderWindow& app)
{
	app.draw(lluvia_cont);
}

