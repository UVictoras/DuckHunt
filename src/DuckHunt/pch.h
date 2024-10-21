#pragma once

#define NOMINMAX 

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DEBUG_NEW
#endif

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include "Shotgun.h"
#include "Bird.h"