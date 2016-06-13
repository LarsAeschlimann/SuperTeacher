//#include <iostream>

#include "Text.h"

Text::Text(std::string text,sf::Vector2f position_on_screen,std::shared_ptr<const sf::Font> font)
{
    std::shared_ptr<sf::Text> temp(std::make_shared<sf::Text>(text, *font, 50));
    temp->setOrigin(position_on_screen);
    m_text.push_back(temp);
    //m_screen_pos = position_on_screen;
}

void Text::Add_Text(std::shared_ptr<sf::Text> text, sf::Vector2f position_on_screen)//, std::shared_ptr<const sf::Font> font)
{
    text->setOrigin(position_on_screen);
    m_text.push_back(text);
}


void Text::update(sf::Vector2f screen_position)
{
    for (auto n : m_text)
    {
        n->setPosition(screen_position);
    }
}

std::vector<std::shared_ptr<sf::Text>> Text::get_texts(void)
{
    return m_text;
}