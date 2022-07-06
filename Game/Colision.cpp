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
	/*
		if (e1.anim.sp.getPosition().y + e1.anim.sp.getGlobalBounds().height > height)
		e1.anim.sp.setPosition(e1.anim.sp.getPosition().x, height - e1.anim.sp.getGlobalBounds().height);
	*/
}

char Colision::colision_pantalla_enemy(sf::Sprite& s1, float& vsx, float& vsy, int width, int height)
{
	if (s1.getPosition().x < 0.f)
		return 'A';
	else if (s1.getPosition().x + s1.getGlobalBounds().width > width)
		return 'D';
	if (s1.getPosition().y < 0.f)
		return 'W';
}

void Colision::colision_platform_player(sf::Sprite& s1, sf::Sprite& s2, float& vsx, float& vsy, float vsx_aux)
{
	sf::FloatRect playerBounds = s1.getGlobalBounds();
	sf::FloatRect wallBounds = s2.getGlobalBounds();
	nextPos = playerBounds;
	nextPos.left += vsx;
	nextPos.top += vsy;

	if (wallBounds.intersects(nextPos))
	{
		//Top Colision
		if (playerBounds.top > wallBounds.top && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
			&& playerBounds.left < wallBounds.left + wallBounds.width && playerBounds.left + playerBounds.width > wallBounds.left)
		{
			//vsy = 0.f;			
			s1.setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
		}
		//Botton Colision
		else if (playerBounds.top < wallBounds.top && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
			&& playerBounds.top < wallBounds.top + wallBounds.height && playerBounds.top + playerBounds.height > wallBounds.top)
		{
			//vsy = 0.f;
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
		vsx = 3.15;
		//vsy = 3.15;
	}
}

void Colision::colision_platform_enemy(sf::Sprite& s1, sf::Sprite& s2, float& vsx, float& vsy, char& Ori)
{
	sf::FloatRect EnemyBounds = s1.getGlobalBounds();
	sf::FloatRect wallBounds = s2.getGlobalBounds();

	nextPos = EnemyBounds;
	nextPos.left += vsx;
	nextPos.top += vsy;

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

bool Colision::colision_entity_entity(sf::Sprite& e1, sf::Sprite e2, float& vsx, float& vsy)
{
	sf::FloatRect e1_Bounds = e1.getGlobalBounds();
	sf::FloatRect e2_Bounds = e2.getGlobalBounds();
	nextPos = e2_Bounds;
	nextPos.left += vsx;
	nextPos.top += vsy;

	if (e1_Bounds.intersects(nextPos))
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


