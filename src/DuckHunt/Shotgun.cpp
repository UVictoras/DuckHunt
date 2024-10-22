#include "pch.h"
#include "Shotgun.h"

void Shotgun::Click()
{
	switch (m_state)
	{
	case State::BarrelFull:
	{
		m_state = State::BarrelEmpty; 
		m_sprite.setTexture(*m_textures[1]); 
		std::thread threadObject(&Shotgun::_ShootTime, this); 
		threadObject.detach(); 
		break;
	}
	case State::BarrelEmpty:
	case State::Reloading:
	default:
		break;
	}
}

void Shotgun::Reload()
{
	switch (m_state)
	{
	case State::BarrelEmpty:
	{
		m_state = State::Reloading;
		std::thread threadObject(&Shotgun::_ReloadBullet, this); 
		threadObject.detach();
		break;
	}
	case State::BarrelFull:
	case State::Reloading:
	default:
		break;
	}
}

std::string Shotgun::GetStateStr()
{
	switch (m_state)
	{
	case State::BarrelFull:
		return "Barrel is Full.";
		break;
	case State::BarrelEmpty:
		return "Barrel is Empty.";
		break;
	case State::Reloading:
	default:
		return "Reloading...";
		break;
	}
}

void Shotgun::LoadTextures()
{
	sf::Texture* texture1 = new sf::Texture(); 
	if (!texture1->loadFromFile("..\\..\\..\\res\\Image\\BarrelFull.png")) 
		return;

	m_textures.push_back(texture1); 

	sf::Texture* texture2 = new sf::Texture(); 
	if (!texture2->loadFromFile("..\\..\\..\\res\\Image\\Clicking.png"))
		return;

	m_textures.push_back(texture2);

	sf::Texture* texture3 = new sf::Texture();
	if (!texture3->loadFromFile("..\\..\\..\\res\\Image\\BarrelEmpty.png"))
		return;

	m_textures.push_back(texture3);

	sf::Texture* texture4 = new sf::Texture();
	if (!texture4->loadFromFile("..\\..\\..\\res\\Image\\Reloading.png"))
		return;

	m_textures.push_back(texture4);

	m_sprite.setPosition({ 0,0 });
	m_sprite.setTexture(*texture1); 
}

void Shotgun::_ReloadBullet()
{
	m_sprite.setTexture(*m_textures[3]);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	m_state = State::BarrelFull;
	m_sprite.setTexture(*m_textures[0]);
}

void Shotgun::_ShootTime()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));  
	m_sprite.setTexture(*m_textures[2]); 
}