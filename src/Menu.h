#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "HIManager.h"
#include "Level.h"


typedef enum
{
    start_new,
    next_level,
    quit
}menu;

typedef struct
{
    std::shared_ptr<sf::Texture> on;
    std::shared_ptr<sf::Texture> off;
    std::shared_ptr<sf::Sprite> sprite;
    std::shared_ptr<sf::Text> text;
    std::string function;
}Button;

class Menu : public Object {

public:
    Menu(std::shared_ptr<ResourceManager> resource);
    void update(level_str level_info, sf::RenderWindow* window);
    void process_event_menu(HIEvent events, std::shared_ptr<const json> config, sf::RenderWindow* window, level_str * level_info);

private:
    std::vector<std::shared_ptr<Button>> buttons;

    std::shared_ptr<sf::Music> song;
};