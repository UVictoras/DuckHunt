#include "pch.h"

void Bird::update(float deltaTime)
{
    if (movingRight)
        sprite.move(speed * deltaTime, 0); 
    else
        sprite.move(-speed * deltaTime, 0); 
}

