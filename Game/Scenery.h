#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Scenary
{
public:
	friend class SceneryBuilder;
	Scenary();
	~Scenary();
	void setScale(float tam_x, float tam_y);
	void cargar_fondo(std::string direccion_fondo);
	void cargar_musica(std::string direccion_musica);
	void setVolumen(float vol);
private:
	sf::Texture tex_fondo;
	sf::Sprite sp_fondo;
	sf::Music musica;
	float tam_x, tam_y;
};
