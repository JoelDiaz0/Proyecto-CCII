#include "Colision.h"

Colision::Colision()
{
}

Colision::~Colision()
{
}

void Colision::colision_pantalla_player(sf::Sprite& s1, int width, int height)
{
	if (s1.getPosition().x < 0.f)
		s1.setPosition(0.f, s1.getPosition().y);

	if (s1.getPosition().y < 0.f)
		s1.setPosition(s1.getPosition().x, 0.f);

	if (s1.getPosition().x + s1.getGlobalBounds().width > width)
		s1.setPosition(width - s1.getGlobalBounds().width, s1.getPosition().y);
}

char Colision::colision_pantalla_enemy(sf::Sprite& s1, int width, int height)
{
	if (s1.getPosition().x < 0.f)
		return 'A';
	else if (s1.getPosition().x + s1.getGlobalBounds().width > width)
		return 'D';
	if (s1.getPosition().y < 0.f)
		return 'W';
}

void Colision::colision_platformMovil_player(sf::Sprite& jugador, sf::Sprite& plataforma)
{
	sf::FloatRect playerBounds = jugador.getGlobalBounds();
	sf::FloatRect wallBounds = plataforma.getGlobalBounds();
	nextPos = playerBounds;

	if (wallBounds.intersects(nextPos))
	{
		//Top Colision
		if (playerBounds.top > wallBounds.top && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
			&& playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left)
		{
			jugador.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
		}
		//Botton Colision
		else if (playerBounds.top < wallBounds.top && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
			&& playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top)
		{
			jugador.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
		}
		//Right Colision
		if (playerBounds.left < wallBounds.left && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
			&& playerBounds.top < wallBounds.top + 10 + wallBounds.height - 10 && playerBounds.top + playerBounds.height > wallBounds.top + 10)
		{
			jugador.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
		}
		//left Colision
		else if (playerBounds.left > wallBounds.left && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
			&& playerBounds.top < wallBounds.top + 10 + wallBounds.height - 10 && playerBounds.top + playerBounds.height > wallBounds.top + 10)
		{
			jugador.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
		}
	}
}

void Colision::colision_platform_player(sf::Sprite& s1, sf::Sprite& s2, float& vsx, float& vsy, float vsx_aux)
{
	sf::FloatRect playerBounds = s1.getGlobalBounds();
	sf::FloatRect wallBounds = s2.getGlobalBounds();
	nextPos = playerBounds;

	if (wallBounds.intersects(nextPos))
	{
		//Top Colision
		if (playerBounds.top > wallBounds.top && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
			&& playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left)
		{			
			s1.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
		}
		//Botton Colision
		else if (playerBounds.top < wallBounds.top && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
			&& playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top)
		{
			s1.setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
		}
		//Right Colision
		if (playerBounds.left < wallBounds.left && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
			&& playerBounds.top < wallBounds.top + 10 + wallBounds.height - 10 && playerBounds.top + playerBounds.height > wallBounds.top + 10)
		{
			vsx = 0.f;
			s1.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
		}
		//left Colision
		else if (playerBounds.left > wallBounds.left && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
			&& playerBounds.top < wallBounds.top + 10 + wallBounds.height - 10 && playerBounds.top + playerBounds.height > wallBounds.top + 10)
		{
			vsx = 0.f;
			s1.setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
		}
	}
	else
	{
		vsx = 3.15f;
	}
}

void Colision::colision_platform_enemy(sf::Sprite& s1, sf::Sprite& s2, float& vsx, float& vsy, char& Ori)
{
	sf::FloatRect EnemyBounds = s1.getGlobalBounds();
	sf::FloatRect wallBounds = s2.getGlobalBounds();
	nextPos = EnemyBounds;

	if (wallBounds.intersects(nextPos))
	{
		//Top Colision
		if (EnemyBounds.top > wallBounds.top && EnemyBounds.top + EnemyBounds.height > wallBounds.top + wallBounds.height
			&& EnemyBounds.left < wallBounds.left + wallBounds.width && EnemyBounds.left + EnemyBounds.width > wallBounds.left)
		{
			s1.setPosition(EnemyBounds.left, wallBounds.top + wallBounds.height);
		}
		//Botton Colision
		else if (EnemyBounds.top < wallBounds.top && EnemyBounds.top + EnemyBounds.height < wallBounds.top + wallBounds.height
			&& EnemyBounds.top < wallBounds.top + wallBounds.height && EnemyBounds.top + EnemyBounds.height > wallBounds.top)
		{
			s1.setPosition(EnemyBounds.left, wallBounds.top - EnemyBounds.height);
		}
		//Right Colision
		if (EnemyBounds.left < wallBounds.left && EnemyBounds.left + EnemyBounds.width < wallBounds.left + wallBounds.width
			&& EnemyBounds.top < wallBounds.top + 10 + wallBounds.height - 10 && EnemyBounds.top + EnemyBounds.height > wallBounds.top + 10)
		{
			Ori = 'A';
			vsx = -vsx;
			s1.setPosition(wallBounds.left - EnemyBounds.width, EnemyBounds.top);
		}
		//left Colision
		else if (EnemyBounds.left > wallBounds.left && EnemyBounds.left + EnemyBounds.width > wallBounds.left + wallBounds.width
			&& EnemyBounds.top < wallBounds.top + 10 + wallBounds.height - 10 && EnemyBounds.top + EnemyBounds.height > wallBounds.top + 10)
		{
			Ori = 'D';
			vsx = -vsx;
			s1.setPosition(wallBounds.left + wallBounds.width, EnemyBounds.top);
		}
	}
}

bool Colision::enemy_final_colision(sf::Sprite& e1, sf::Sprite& plt1, float& vsx)
{
	sf::FloatRect e1_Bounds = e1.getGlobalBounds();
	sf::FloatRect plt1_Bounds = plt1.getGlobalBounds();
	nextPos = e1_Bounds;
	nextPos.left += (vsx);
	if (!plt1_Bounds.intersects(nextPos) && plt1_Bounds.intersects(e1_Bounds))
		return true;
	return false;
}

bool Colision::colision_bullet_window(sf::Sprite b1, int width, int height)
{
	if (b1.getPosition().x < 0.f || b1.getPosition().y < 0.f || b1.getPosition().x + b1.getGlobalBounds().width > width
		|| b1.getPosition().y + b1.getGlobalBounds().height > height)
	{
		return true;
	}
	return false;
}

bool Colision::colision_entity_entity(sf::Sprite& e1, sf::Sprite& e2)
{
	sf::FloatRect e2Bounds = e2.getGlobalBounds();
	sf::FloatRect e1Bounds = e1.getGlobalBounds();
	nextPos = e2Bounds;
	if (e1Bounds.intersects(nextPos))
	{
		//Top Colision
		if (e2Bounds.top > e1Bounds.top && e2Bounds.top + e2Bounds.height > e1Bounds.top + e1Bounds.height
			&& e2Bounds.left < e1Bounds.left + e1Bounds.width && e2Bounds.left + e2Bounds.width > e1Bounds.left)
		{
			return true;
		}
		//Botton Colision
		else if (e2Bounds.top < e1Bounds.top && e2Bounds.top + e2Bounds.height < e1Bounds.top + e1Bounds.height
			&& e2Bounds.top < e1Bounds.top + e1Bounds.height && e2Bounds.top + e2Bounds.height > e1Bounds.top)
		{
			return true;
		}
		//Right Colision
		if (e2Bounds.left < e1Bounds.left && e2Bounds.left + e2Bounds.width < e1Bounds.left + e1Bounds.width
			&& e2Bounds.top < e1Bounds.top + e1Bounds.height && e2Bounds.top + e2Bounds.height > e1Bounds.top)
		{
			return true;
		}
		//left Colision
		else if (e2Bounds.left > e1Bounds.left && e2Bounds.left + e2Bounds.width > e1Bounds.left + e1Bounds.width
			&& e2Bounds.top < e1Bounds.top + e1Bounds.height && e2Bounds.top + e2Bounds.height > e1Bounds.top)
		{
			return true;
		}
	}
    return false;
}


