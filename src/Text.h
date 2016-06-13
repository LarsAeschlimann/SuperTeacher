#pragma once
#include "Object.h"

#include <string>
#include <SFML/Graphics.hpp>

class Text : public Object {
public:
    Text(std::string text, sf::Vector2f position_on_screen, std::shared_ptr<const sf::Font> font);
    void Add_Text(std::shared_ptr<sf::Text> text, sf::Vector2f position_on_screen);
    void update(sf::Vector2f screen_position);
    std::vector<std::shared_ptr<sf::Text>> get_texts(void);
    
private:
    sf::Vector2f m_screen_pos;
    std::vector<std::shared_ptr<sf::Text>> m_text;
};
