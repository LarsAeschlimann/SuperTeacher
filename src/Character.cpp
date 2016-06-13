//
//  Background.cpp
//  SuperTeacher
//
//  Created by Samuel Dolt on 03.05.16.
//
//

#include "Character.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include "Physics.h"

Character::Character(std::shared_ptr<ResourceManager> resource, std::string level_name, int GroundLevel){


    
    m_resource = resource;
    auto level = m_resource->get_json("levels/" + level_name + ".json");
    
    colisi.walk_level = GroundLevel*BLOCK_PXSIZE;
    
    m_live = ((int)(*level)["init"]["lives"]);
    auto animation_texture = resource->get_texture("graphics/characters/spritefile.png");
    m_animation = std::make_shared<sf::Sprite>();
    m_animation->setTexture(*animation_texture);
    animation_texture->setSmooth(true);
<<<<<<< HEAD
    m_animation->setScale(0.35,  0.35);
    m_animation->setOrigin(0, colisi.walk_level);// m_animation->getGlobalBounds().height);// +BLOCK_PXSIZE); // TROUVER D'OU VIENT LE BLOCK DE DECALAGE, ET ENLEVER CELUI-CI
    m_animation->move(10,colisi.walk_level);

    m_animation->setScale((float)0.4, (float)0.4);
=======
    m_animation->setScale((float)0.35, (float)0.35);
>>>>>>> BFH-E1D-2015-2016/master
    m_animation->setOrigin((float)0, (float)colisi.walk_level);
    m_animation->move((float)10, (float)colisi.walk_level);
    m_animation->setTextureRect(sf::IntRect(0 * 660,  100, 700, 1100));

    add_drawable(m_animation);
    jumpLevel = JUMP;
    m_nb_pencils = 0;
    flag1 = true;
}

void Character::process_event(HIEvent event){

    static int move_step = 0;
    static int counter = 0;
    float posx;
    float posy;
    static int speed = SPEED;
    static int direction = 1;
    
    switch(event) {
        case HIEvent::GO_LEFT:
            direction = -1;
            if(colisi.left_enable)
            {
                m_animation->move((float)-speed, (float)0);
            }
            if (flag1)
            {
                move_step = 0;
                flag1 = false;
            }
            if(m_animation->getPosition().y >= colisi.walk_level)
            {
                m_animation->setTextureRect(sf::IntRect(move_step * 670, 1150 + 100,700,1100));
                counter++;
                if(counter >= 25/speed)
                {
                    move_step++;
                    counter = 0;
                }
                if(move_step >= 8)
                {
                    move_step = 0;
                }
            }
            else
            {
                m_animation->setTextureRect(sf::IntRect(8 * 676, 1150 + 80,900,1120));
            }
            break;
        case HIEvent::FAST_DOWN:
            speed = 2*SPEED;
            jumpLevel = JUMP * 4 / 3;
            break;
        case HIEvent::FAST_UP:
            speed = SPEED;
            jumpLevel = JUMP;
            break;
        case HIEvent::GO_RIGHT:
            direction = 1;
            if(colisi.right_enable)
            {
                m_animation->move((float)speed, (float)0);
            }
            if (!flag1)
            {
                move_step = 0;
                flag1 = true;
            }
            if(m_animation->getPosition().y >= colisi.walk_level)
            {
                m_animation->setTextureRect(sf::IntRect(move_step * 660,100,700,1100));
                counter++;
                if(counter >= 25/speed)
                {
                    move_step++;
                    counter = 0;
                }
                if(move_step >= 8)
                {
                    move_step = 0;
                }
            }
            else
            {
                m_animation->setTextureRect(sf::IntRect(9 * 590, 80,900,1120));
            }
            break;

        case HIEvent::JUMP:
            
            jump_manager(m_animation, (float)colisi.walk_level, -jumpLevel);
            if(flag1)
            {
                m_animation->setTextureRect(sf::IntRect(9 * 590, 80,900,1120));
            }
            else
            {
                m_animation->setTextureRect(sf::IntRect(8 * 676, 1150 + 80,900,1120));
            }
            break;
        case HIEvent::THROW:
            if (m_nb_pencils > 0)
            {
                posy = (float)(get_rectangle().top + get_rectangle().height / 2.0-THROW_LEVEL);
                posx = (float)(get_rectangle().left + get_rectangle().width / 2.0);
                m_pencils.push_back(Pencil(m_resource, posx, posy, direction));
                if (flag1)
                {
                    m_animation->setTextureRect(sf::IntRect(0 * 660,  100, 700, 1100));
                }
                else
                {
                    m_animation->setTextureRect(sf::IntRect(0 * 670,  1150 + 100, 700, 1100));
                }
                m_nb_pencils--;
            }
            break;
        case HIEvent::KEY_UP:
            if(m_animation->getPosition().y >= colisi.walk_level)
            {
                if(flag1)
                {
                    m_animation->setTextureRect(sf::IntRect(0 * 660, 100,700,1100));
                }
                else
                {
                    m_animation->setTextureRect(sf::IntRect(0 * 670, 1150 + 100,700,1100));
                }
            }
            break;
        default:
            break;
    }
}



void Character::update()
{
    m_animation->move((float)colisi.x_move, 0);
    int y_moins1 = (int)m_animation->getPosition().y;
    jump_manager(m_animation, (float)colisi.walk_level, 0);
    if (m_animation->getPosition().y >= colisi.walk_level && y_moins1 < colisi.walk_level)
    {
        if (flag1)
        {
            m_animation->setTextureRect(sf::IntRect(0 * 660,  100, 700, 1100));
        }
        else
        {
            m_animation->setTextureRect(sf::IntRect(0 * 670,  1150 + 100, 700, 1100));
        }
    }
    
    for (auto p : m_pencils){
        p.update();
    }
    
}

int Character::getCharacterLevel(void)
{
    return (int)m_animation->getPosition().y;
}

int Character::getNbPencil(void)
{
    return m_nb_pencils;
}

sf::FloatRect Character::get_rectangle(void)
{
    return m_animation->getGlobalBounds();
}


void Character::write_collision(colision coll)
{
    colisi = coll;
}

std::vector<std::shared_ptr<sf::Drawable>> Character::get_drawables(void)
{
    std::vector<std::shared_ptr<sf::Drawable>> drawable;
    
    for(auto n: m_drawable){
        drawable.push_back(n);
    }
    for(auto n: m_pencils)
    {
        for(auto m: n.get_drawables()){
            drawable.push_back(m);
        }
    }
    
    return drawable;
}

void Character::addPencil(int nb)
{
    m_nb_pencils += nb;
}

std::vector<Pencil> Character::getPencil(void)
{
    return m_pencils;
}

void Character::setPencil(std::vector<Pencil> new_pencils)
{
    m_pencils = new_pencils;
}

void Character::addLive(int val)
{
    m_live += val;
}

int Character::getLive(void)
{
    return m_live;
}