#include "pch.h"
#include "main.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Duck Hunt");

	window.clear();
	window.display();

    sf::Texture texture;
    if (!texture.loadFromFile("..\\..\\..\\res\\Image\\Crosshair.png"))
        return -1;

    sf::Sprite crosshair;
    crosshair.setTexture(texture);

    sf::Vector2u textureSize = texture.getSize();

    float desiredWidth = 40.0f;
    float desiredHeight = 40.0f;

    float scaleX = desiredWidth / textureSize.x;
    float scaleY = desiredHeight / textureSize.y;

    crosshair.setScale(scaleX, scaleY);

    crosshair.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f); 

    sf::Texture backGroundTexture;
    if (!backGroundTexture.loadFromFile("..\\..\\..\\res\\Image\\Background.jpg")) 
        return -1;

    sf::Sprite background;
    background.setTexture(backGroundTexture);
       
    sf::Vector2i mousePosition;

    sf::Vector2f worldPosition;

    Shotgun shotgun;
    shotgun.LoadTextures();

    sf::Texture birdTexture; 
    if (!birdTexture.loadFromFile("..\\..\\..\\res\\Image\\Bird.png")) 
        return -1;

    std::vector<Bird> birds; 

    sf::Clock spawnClock; 
    sf::Time spawnInterval = sf::seconds(2.0f); 

    sf::Clock deltaTimeClock; 

    std::srand(static_cast<unsigned>(std::time(0)));

    int score = 0; 

    sf::Font font; 
    if (!font.loadFromFile("..\\..\\..\\res\\m29.ttf"))  
        return -1;

    sf::Text scoreText; 
    scoreText.setFont(font); 
    scoreText.setCharacterSize(24);  
    scoreText.setFillColor(sf::Color::White);  

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = deltaTimeClock.restart().asSeconds(); 

        if (spawnClock.getElapsedTime() >= spawnInterval) 
        {
            spawnClock.restart(); 

            bool spawnOnRight = std::rand() % 2; 

            float yPos = static_cast<float>(std::rand() % 600); 

            float speed = 100.0f; 
             
            if (spawnOnRight) 
            {
                birds.emplace_back(birdTexture, 800.0f, yPos, speed, false); 
            }
            else
            {
                birds.emplace_back(birdTexture, 0.0f, yPos, speed, true);  
            }
        }

        for (auto& bird : birds) 
        {
            bird.update(deltaTime); 
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window); 
            sf::Vector2f mousePosFloat = window.mapPixelToCoords(mousePosition); 

            for (auto it = birds.begin(); it != birds.end();) 
            {
                if (it->isClicked(mousePosFloat) && shotgun.GetStateStr() == "Barrel is Full.")
                {             
                    score += 100;  
                    it = birds.erase(it);
                }
                else
                {
                    ++it;  
                }
            }
            shotgun.Click(); 
        } 

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) 
        {
            shotgun.Reload(); 
        }

        mousePosition = sf::Mouse::getPosition(window);

        worldPosition = window.mapPixelToCoords(mousePosition);

        crosshair.setPosition(worldPosition);

        scoreText.setString("Score : " + std::to_string(score)); 

        window.clear();

        window.draw(background);
        window.draw(shotgun.m_sprite); 
        for (Bird bird : birds) 
        {
            window.draw(bird.getSprite()); 
        }

        window.draw(crosshair);

        scoreText.setPosition(window.getSize().x - scoreText.getGlobalBounds().width - 10, 10);
        window.draw(scoreText); 

        window.display();
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
