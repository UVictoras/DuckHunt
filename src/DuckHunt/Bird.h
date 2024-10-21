#pragma once
#include <SFML/Graphics.hpp>

class Bird
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
    bool movingRight;

public:
    Bird(const sf::Texture& texture, float startX, float startY, float speed, bool movingRight)
        : sprite(texture), speed(speed), movingRight(movingRight)
    {
        sprite.setPosition(startX, startY);

        sf::Vector2u textureSize = texture.getSize();

        float scaleX = 53.0f / textureSize.x; 
        float scaleY = 40.0f / textureSize.y; 
         
        sprite.setScale(scaleX, scaleY); 

        sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f); 

        if (!movingRight) 
        {
            sprite.setScale(-scaleX, scaleY); 
        }
    }

    void update(float deltaTime);

    bool isClicked(sf::Vector2f mousePos)
    {
        return sprite.getGlobalBounds().contains(mousePos);
    }

    sf::Sprite& getSprite() { return sprite; }
};