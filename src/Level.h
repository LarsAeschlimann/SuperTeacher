#pragma once
#include <iostream>
#include <memory>
#include <time.h>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Constants.h"
#include "Path.h"
#include "AbstractView.h"
#include "ResourceManager.h"
#include "HIManager.h"
#include "Logs.h"
#include "Object.h"
#include "Background.h"
#include "Ground.h"
#include "Physics.h"
#include "Character.h"
#include "View.h"
#include "Text.h"
#include "Interactives.h"

void level_execute(level_str* level_info, sf::RenderWindow* window);