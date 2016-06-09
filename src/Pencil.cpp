//
//  Sol.cpp
//  SuperTeacher
//
//  Created by Etienne Houriet on 17.05.16.
//
//

#include "Pencil.h"
#include "Constants.h"

Pencil::Pencil(std::shared_ptr<ResourceManager> resource, float posx, float posy, int direction) {
    
    m_direction = direction;
    m_resource = resource;
    m_pencil = std::make_shared<sf::Sprite>();
    m_pencil->setScale(0.1, 0.1);
    m_pencil->setPosition(posx, posy);
    auto pencil_texture = resource->get_texture("graphics/characters/pencil.png");
    m_pencil->setTexture(*pencil_texture);
    
    add_drawable(m_pencil);
}


void Pencil::update(void){

    m_pencil->move(m_direction * 20,0);
    m_pencil->rotate(1);
}

sf::FloatRect Pencil::get_rectangle(void)
{
    return m_pencil->getGlobalBounds();
}