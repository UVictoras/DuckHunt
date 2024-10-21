#pragma once

class Shotgun
{
public:
    enum class State
    {
        BarrelFull,
        BarrelEmpty,
        Reloading,
    };

private:
    State                       m_state;
    std::vector<sf::Texture*>    m_textures;

public:
    sf::Sprite                  m_sprite;

    Shotgun() : m_state(State::BarrelFull) { };
    ~Shotgun() { };

    void                        Click();
    void                        Reload();
    std::string                 GetStateStr();

    void                        LoadTextures();

private:
    void                        _ReloadBullet();
    void                        _ShootTime();
};