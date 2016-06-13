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
    
    auto superteacher_texture = resource->get_texture("graphics/characters/superteacher.png");
    m_superteacher = std::make_shared<sf::Sprite>();
    m_superteacher->setTexture(*superteacher_texture);
    colisi.walk_level = GroundLevel*BLOCK_PXSIZE;//658 - ( BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS) - (int)(*level)["ground"]["level"] ));
    //m_superteacher->move(0,colisi.walk_level);
    
    m_live = ((int)(*level)["init"]["lives"]);
    auto animation_texture = resource->get_texture("graphics/characters/spritefile.png");
    m_animation = std::make_shared<sf::Sprite>();
    m_animation->setTexture(*animation_texture);
    animation_texture->setSmooth(true);
    m_animation->setScale(0.35,  0.35);
    m_animation->setOrigin(0, colisi.walk_level);// m_animation->getGlobalBounds().height);// +BLOCK_PXSIZE); // TROUVER D'OU VIENT LE BLOCK DE DECALAGE, ET ENLEVER CELUI-CI
    m_animation->move(10,colisi.walk_level);
    m_animation->setTextureRect(sf::IntRect(0 * 660,  100, 700, 1100));
    /*
    auto animation_student_texture = resource->get_texture("graphics/characters/student.png");
    m_student_animation = std::make_shared<sf::Sprite>();
    m_student_animation->setTexture(*animation_student_texture);
    animation_texture->setSmooth(true);
    m_student_animation->move(800,colisi.walk_level);
    m_student_animation->setScale(0.25, 0.25);
    
    auto transparent_texture = resource->get_texture("graphics/characters/transparent.png");
    m_transparent = std::make_shared<sf::Sprite>();
    m_transparent->setTexture(*transparent_texture);
    
    static sf::Vector2i source(0,0);
    m_animation->setTextureRect(sf::IntRect(source.x * 660,source.y,700,1200));
   */
    add_drawable(m_animation);
    jumpLevel = JUMP;
    m_nb_pencils = 0;
}

void Character::process_event(HIEvent event){

    static sf::Vector2i source(0,0);
    static int counter1 = 0;
    static int flag = 0;
    static int flag1 = 1;
    static int flag2 = 0;
    static int collisionflag1 = 0;
    static int collisionflag2 = 0;
    float posx;
    float posy;
    static int speed = SPEED;
    static int direction = 1;
    
    switch(event) {
        case HIEvent::GO_LEFT:
            direction = -1;
            if(colisi.left_enable)
            {
                m_animation->move(-speed,0);
                collisionflag1 = 0;
                collisionflag2 = 1;
            }
            if (flag2 == 0)
            {
                source.x = 0;
                flag2 = 1;
                flag1 = 0;
            }
            if(m_animation->getPosition().y == colisi.walk_level)
            /*{
                flag = 0;
            }
            if(flag == 0)*/
            {
                /*if (flag2 == 0)
                {
                    source.x = 0;
                    flag2 = 1;
                    flag1 = 0;
                }*/
                source.y = 1;
                m_animation->setTextureRect(sf::IntRect(source.x * 670,source.y * 1150 + 100,700,1100));
                counter1++;
                if(counter1 >= 25/speed)
                {
                    source.x++;
                    counter1 = 0;
                }
                if(source.x >= 8)
                {
                    source.x = 0;
                }
            }
            else
            {
                source.y = 1;
                m_animation->setTextureRect(sf::IntRect(8 * 676,source.y * 1150 + 80,900,1120));
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
                m_animation->move(speed,0);
                collisionflag1 = 1;
                collisionflag2 = 0;
            }
            if (flag1 == 0)
            {
                source.x = 0;
                flag1 = 1;
                flag2 = 0;
            }
            if(m_animation->getPosition().y == colisi.walk_level)
            /*{
                flag = 0;
            }
            if(flag == 0)*/
            {
                /*if(flag1 == 0)
                {
                    source.x = 0;
                    flag1 = 1;
                    flag2 = 0;
                }*/
                m_animation->setTextureRect(sf::IntRect(source.x * 660,source.y+100,700,1100));
                counter1++;
                if(counter1 >= 25/speed)
                {
                    source.x++;
                    counter1 = 0;
                }
                if(source.x >= 8)
                {
                    source.x = 0;
                }
            }
            else
            {
                m_animation->setTextureRect(sf::IntRect(9 * 590,source.y + 80,900,1120));
            }
            break;

        case HIEvent::JUMP:
            
            jump_manager(m_animation, colisi.walk_level, -jumpLevel, 0);
            flag = 1;
            if(flag1 == 1)
            {
                m_animation->setTextureRect(sf::IntRect(9 * 590,source.y + 80,900,1120));
            }
            else
            {
                source.y = 1;
                m_animation->setTextureRect(sf::IntRect(8 * 676,source.y * 1150 + 80,900,1120));
            }
            break;
        case HIEvent::GO_UP:
            //jumpLevel--;
            break;
        case HIEvent::GO_DOWN:
            //jumpLevel++;
            break;
        case HIEvent::THROW:
            if (m_nb_pencils > 0)
            {
                posy = get_rectangle().top + get_rectangle().height / 2.0;
                posx = get_rectangle().left + get_rectangle().width / 2.0;
                m_pencils.push_back(Pencil(m_resource, posx, posy, direction));
                if (flag1 == 1)
                {
                    m_animation->setTextureRect(sf::IntRect(0 * 660, source.y + 100, 700, 1100));
                }
                else
                {
                    source.y = 1;
                    m_animation->setTextureRect(sf::IntRect(0 * 670, source.y * 1150 + 100, 700, 1100));
                }
                m_nb_pencils--;
            }
            break;
        default:
            if(m_animation->getPosition().y == colisi.walk_level)
            {
                flag = 0;
                if(flag1 == 1)
                {
                    m_animation->setTextureRect(sf::IntRect(0 * 660,source.y + 100,700,1100));
                }
                else
                {
                    source.y = 1;
                    m_animation->setTextureRect(sf::IntRect(0 * 670,source.y * 1150 + 100,700,1100));
                }
            }
            break;
    }
}



void Character::update()
{
    int collisionflag3 = 0;
   /* if(!get_rectangle().intersects(m_student_animation->getGlobalBounds()))
    {
        collisionflag3 = 0;
    }
    */
    m_animation->move(colisi.x_move, 0);
    jump_manager(m_animation, colisi.walk_level, 0,collisionflag3);
    
    for (auto p : m_pencils){
        p.update();
    }
    
}

int Character::getCharacterLevel(void)
{
    return m_animation->getPosition().y;
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