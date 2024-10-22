#pragma once
#include <SFML/Graphics.hpp>

class Bird
{
    enum class BirdState
    {
        State1,
        State2,
        State3,
        Shot,
        Falling 
    };

private:
    BirdState m_state;
    sf::Sprite sprite;
    std::vector<sf::Texture*> m_textures;
    float speed; 
    bool movingRight; 
    bool isFalling;
    sf::Vector2f m_currentPosition;

public:
    Bird(float startX, float startY, float speed, bool movingRight)
        : speed(speed), movingRight(movingRight), m_state(BirdState::State1), isFalling(false)
    {
        sprite.setPosition({ startX, startY });
    }

    void update(float deltaTime);

    bool isClicked(sf::Vector2f mousePos);

    void LoadTextures(int seed);

    void GotShot();

    void ChangeTextureToState();

    void RotateStates();

    sf::Sprite& getSprite() { return sprite; }

private:
    void _Fall();
};