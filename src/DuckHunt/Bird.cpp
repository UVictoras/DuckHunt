#include "pch.h"

void Bird::update(float deltaTime)
{
    if (isFalling == true)
    {
        sprite.move(0, speed * deltaTime);
        return;
    }

    if (movingRight)
    {
        sprite.move(-speed * deltaTime, 0);  
        if (sprite.getScale().x > 0) 
        {
            sprite.setScale(-std::abs(sprite.getScale().x), sprite.getScale().y); 
        }
    }
    else
    {
        sprite.move(speed * deltaTime, 0);  
        if (sprite.getScale().x < 0) 
        {
            sprite.setScale(std::abs(sprite.getScale().x), sprite.getScale().y); 
        }
    }
}

bool Bird::isClicked(sf::Vector2f mousePos)
{
    return sprite.getGlobalBounds().contains(mousePos);
}

void Bird::LoadTextures(int seed)
{
    std::string color;
    switch (seed)
    {
    case 0:
    case 1:
        color = "RedBird";
        break;
    case 2:
        color = "BlueBird";
        break;
    case 3:
    default:
        color = "BlackBird";
        break;
    }

    sf::Texture* texture1 = new sf::Texture();
    if (!texture1->loadFromFile("..\\..\\..\\res\\Image\\" + color + "\\State1.png"))
        return;

    m_textures.push_back(texture1);

    sf::Texture* texture2 = new sf::Texture();
    if (!texture2->loadFromFile("..\\..\\..\\res\\Image\\" + color + "\\State2.png"))
        return;

    m_textures.push_back(texture2);

    sf::Texture* texture3 = new sf::Texture();
    if (!texture3->loadFromFile("..\\..\\..\\res\\Image\\" + color + "\\State3.png"))
        return;

    m_textures.push_back(texture3);

    sf::Texture* texture4 = new sf::Texture();
    if (!texture4->loadFromFile("..\\..\\..\\res\\Image\\" + color + "\\Shot.png"))
        return;

    m_textures.push_back(texture4);

    sf::Texture* texture5 = new sf::Texture();
    if (!texture5->loadFromFile("..\\..\\..\\res\\Image\\" + color + "\\Falling.png"))
        return;

    m_textures.push_back(texture5);

    sprite.setTexture(*texture1);

    sf::Vector2u textureSize = texture1->getSize();
    sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);

    if (!movingRight)
    {
        sprite.setScale(-1.f, 1.f); 
    }
}

void Bird::GotShot()
{
    sprite.setScale(1.f, 1.f);  
    m_state = BirdState::Shot;

    sf::Vector2u textureSize = sprite.getTexture()->getSize();
    sprite.setScale(1.07f, 1.45f); 

    std::thread threadObject(&Bird::_Fall, this);
    threadObject.detach();
}

void Bird::ChangeTextureToState()
{
    m_currentPosition = sprite.getPosition();
    switch (m_state)
    {
    case BirdState::State1:
        if (sprite.getTexture() != m_textures[0])
            sprite.setTexture(*m_textures[0]);
        break;
    case BirdState::State2:
        if (sprite.getTexture() != m_textures[1])
            sprite.setTexture(*m_textures[1]);
        break;
    case BirdState::State3:
        if (sprite.getTexture() != m_textures[2])
            sprite.setTexture(*m_textures[2]);
        break;
    case BirdState::Shot:
        if (sprite.getTexture() != m_textures[3])
            sprite.setTexture(*m_textures[3]);
        break;
    case BirdState::Falling:
        if (sprite.getTexture() != m_textures[4])
            sprite.setTexture(*m_textures[4]);
        break;
    }

    if (!movingRight && sprite.getScale().x > 0)
    {
        sprite.setScale(-std::abs(sprite.getScale().x), sprite.getScale().y);  
    }
    else if (movingRight && sprite.getScale().x < 0)
    {
        sprite.setScale(std::abs(sprite.getScale().x), sprite.getScale().y);  
    }
}

void Bird::RotateStates()
{
    switch (m_state)
    {
    case BirdState::State1:
        m_state = BirdState::State2;
        break;
    case BirdState::State2:
        m_state = BirdState::State3;
        break;
    case BirdState::State3:
        m_state = BirdState::State1;
        break;
    }
}

void Bird::_Fall()
{
    isFalling = true;
    std::this_thread::sleep_for(std::chrono::seconds(1)); 

    m_state = BirdState::Falling;

    sf::Vector2u textureSize = sprite.getTexture()->getSize();
    sprite.setScale(1.f, 1.f); 

    sprite.setScale(0.59f, 1.02f); 
}
