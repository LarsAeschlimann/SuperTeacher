//
//  Interactives.cpp
//  SuperTeacher
//
//  Created by Etienne Houriet on 06.06.16.
//
//

#include <algorithm>
#include "Interactives.h"
#include "Constants.h"
#include <SFML/Window.hpp>

function_enum string_conv(std::string text)
{
    function_enum convert_val=nothing;
    if (text == "platform")
    {
        convert_val = platform;
    }
    if (text == "bonus")
    {
        convert_val = bonus;
    }
    if (text == "mob")
    {
        convert_val = mob;
    }
    if (text == "charge")
    {
        convert_val = charge;
    }
    if (text == "live")
    {
        convert_val = live;
    }
    if (text == "mouse")
    {
        convert_val = mouse;
    }
    if (text == "end")
    {
        convert_val = end;
    }
    return convert_val;
}

Interactives::Interactives(std::shared_ptr<ResourceManager> resource, std::string level_name) {

    m_resource = resource;

    auto level = m_resource->get_json("levels/" + level_name + ".json");

    auto objects = (*level)["interactive"];
    for (auto object : objects) {
        auto sprite = std::make_shared<act_pack>();
        sprite->function = string_conv(object["function"]);
        auto temp = std::make_shared<sf::Sprite>();
        std::string name = object["image"];
        auto texture = m_resource->get_texture("graphics/" + name + ".png");
        temp->setTexture(*texture);
        if (sprite->function != mouse)
        {
            float x = object["x"];
            float y = object["y"];
            temp->setScale(object["size"], object["size"]);
            sprite->scale = object["size"];
            temp->move(x*BLOCK_PXSIZE, y*BLOCK_PXSIZE - temp->getGlobalBounds().height);
        }
        else
        {
            temp->setTextureRect(sf::IntRect(0, 0, 10, 10));
            temp->setColor(sf::Color::Green);
        }
        sprite->sprite = temp;
        if (sprite->function == mob || sprite->function == bonus || sprite->function == charge || sprite->function == live)
        {
            sprite->value = object["value"];
        }
        if (sprite->function == live)
        {
            sprite->sprite->setOrigin(sprite->sprite->getLocalBounds().width/2, 0);
            //sprite->sprite->move(-sprite->sprite->getLocalBounds().width / 2, sprite->sprite->getLocalBounds().height / 2);
        }
        sprite->use = false;
        sprite->deleteFlag = false;
        m_sprites.push_back(sprite);
        //add_drawable(sprite->sprite);
    }
    auto sprite1 = std::make_shared<act_pack>();
    auto temp1 = std::make_shared<sf::Sprite>();
    auto texture = m_resource->get_texture("graphics/interactives/blanc.png");
    temp1->setTexture(*texture);
    sprite1->sprite = temp1;
    sprite1->sprite->setTextureRect(sf::IntRect(0, 0, SECUR_SPACE, ((int)(*level)["background"]["world"]["y"])*BLOCK_PXSIZE+SECUR_SPACE*10));
    sprite1->function = platform;
    sprite1->use = false;
    sprite1->value = 0;
    sprite1->deleteFlag = false;
    sprite1->sprite->setPosition(-SECUR_SPACE, -SCREEN_Y_PXSIZE - SECUR_SPACE * 10);
    m_sprites.push_back(sprite1);
    auto sprite2 = std::make_shared<act_pack>();
    auto temp2 = std::make_shared<sf::Sprite>();
    temp2->setTexture(*texture);
    sprite2->sprite = temp2;
    sprite2->sprite->setTextureRect(sf::IntRect(0, 0, SECUR_SPACE, ((int)(*level)["background"]["world"]["y"])*BLOCK_PXSIZE + SECUR_SPACE * 10));
    sprite2->function = platform;
    sprite2->use = false;
    sprite2->value = 0;
    sprite2->deleteFlag = false;
    sprite2->sprite->setPosition(((int)(*level)["background"]["world"]["x"])*BLOCK_PXSIZE, -SCREEN_Y_PXSIZE - SECUR_SPACE * 10);
    m_sprites.push_back(sprite2);

}


level_str Interactives::update(Character& mainPerson, std::shared_ptr<sf::Text> score, int GroundLevel,colision *col, int *points)
{
    //static colision col = {true,true,GroundLevel,0};
    level_str level;
    static float val = 0;
    val += 0.2;
    //static int points = startscore;
    bool no_col = true;
    bool del_pack = false;
    bool del_pen = false;
    bool fly = false;
    bool tuch = false;
    auto rect = mainPerson.get_rectangle();
    auto pencil = mainPerson.getPencil();
    //void *supp = NULL;
    //col.walk_level = GroundLevel;//658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
    col->right_enable = true;
    col->left_enable = true;
    col->x_move = 0;
    level.end = false;
    if (col->walk_level == mainPerson.getCharacterLevel())
    {
        fly = false;
    }
    else
    {
        fly = true;
    }
    col->walk_level = GroundLevel;
    for (auto& pack : m_sprites)
    {
        if (pack->sprite->getGlobalBounds().intersects(sf::Rect<float>(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, 1, 1)) &&
            pack->function != mouse)
        {
            tuch = true;
        }
        if (pack->function == platform)
        {
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {

                if (((rect.top+rect.height) <= pack->sprite->getGlobalBounds().top + SECUR_SPACE &&
                    rect.left < pack->sprite->getGlobalBounds().left+pack->sprite->getGlobalBounds().width - 1 &&
                    rect.left + rect.width > pack->sprite->getGlobalBounds().left + 1) )//||
                    //((rect.top + rect.height) <= pack->sprite->getGlobalBounds().top + 1 &&
                    //rect.left < pack->sprite->getGlobalBounds().left+pack->sprite->getGlobalBounds().width - 10 &&
                    //rect.left + rect.width > pack->sprite->getGlobalBounds().left + 10))
                {
                    col->walk_level = pack->sprite->getGlobalBounds().top+1;// - rect.height + 1;
                    if (rect.left + rect.width < pack->sprite->getGlobalBounds().left + SECUR_SPACE)
                    { 
                        if (!fly)
                        {
                            col->x_move = pack->sprite->getGlobalBounds().left - (rect.left + rect.width+SECUR_SPACE);//SECUR_SPACE;
                        }
                        else
                        {
                            col->x_move = SECUR_SPACE*2;
                        }
                    }
                    else if (rect.left > pack->sprite->getGlobalBounds().left +pack->sprite->getGlobalBounds().width -SECUR_SPACE)
                    {
                        if (!fly)
                        {
                            col->x_move = pack->sprite->getGlobalBounds().left - rect.left + pack->sprite->getGlobalBounds().width;
                        }
                        else
                        {
                            col->x_move = -SECUR_SPACE;
                        }
                    }
                }
                
                else if (rect.left + rect.width < pack->sprite->getGlobalBounds().left + pack->sprite->getGlobalBounds().width / 2 &&
                    (rect.top + rect.height) > pack->sprite->getGlobalBounds().top + SECUR_SPACE)// &&
                    //(rect.top + rect.height) < pack->sprite->getGlobalBounds().top + SECUR_SPACE)
                {
                    col->x_move =  pack->sprite->getGlobalBounds().left-(rect.left + rect.width);
                    col->left_enable = false;
                }
                else if (rect.left > pack->sprite->getGlobalBounds().left - pack->sprite->getGlobalBounds().width / 2 + pack->sprite->getGlobalBounds().width &&
                    (rect.top + rect.height) > pack->sprite->getGlobalBounds().top + SECUR_SPACE) //&&
                    //(rect.top + rect.height) < pack->sprite->getGlobalBounds().top + SECUR_SPACE)
                {
                    col->x_move = pack->sprite->getGlobalBounds().left - rect.left +  pack->sprite->getGlobalBounds().width;
                    col->right_enable = false;
                }
                /*else if (rect.left + rect.width / 2 >= pack->sprite->getGlobalBounds().left + pack->sprite->getGlobalBounds().width / 2&&
                         (rect.top + rect.height) > pack->sprite->getGlobalBounds().top + SECUR_SPACE)
                {
                    col.left_enable = false;
                    //col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
                }
                else if((rect.top + rect.height) > pack->sprite->getGlobalBounds().top + SECUR_SPACE)
                {
                    col.right_enable = false;
                    //col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
                }*/
                no_col = false;
            }
        }
        if (pack->function == bonus)
        {
            pack->sprite->setScale(pack->scale + (pack->scale*sin(val/FLASH_SPEED_FACTOR) / FLASH_SIZE_FACTOR), pack->scale + (pack->scale*sin(val/FLASH_SPEED_FACTOR) / FLASH_SPEED_FACTOR));
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                *points += pack->value;
                pack->deleteFlag = true;
                del_pack = true;
            }

        }
        if (pack->function == charge)
        {
            pack->sprite->setScale(pack->scale + (pack->scale*sin(val / FLASH_SPEED_FACTOR) / FLASH_SIZE_FACTOR), pack->scale + (pack->scale*sin(val / FLASH_SPEED_FACTOR) / FLASH_SPEED_FACTOR));
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                mainPerson.addPencil(pack->value);
                pack->deleteFlag = true;
                del_pack = true;
            }

        }
        if (pack->function == mob)
        {
            pack->sprite->move(cos(val / 5) * 10, 0);
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                if (pack->use == false)
                {
                    *points -= pack->value;
                    mainPerson.addLive(-pack->value);
                    if (mainPerson.getLive() <= 0)
                    {
                        level.end = true;
                    }
                }
                pack->use = true;
            }
            else
            {
                pack->use = false;
            }
            for(auto& pen : pencil)
            {
                if (pen.get_rectangle().intersects(pack->sprite->getGlobalBounds()))
                {
                    pack->deleteFlag = true;
                    del_pack = true;
                    //break;
                }
            }
        }
        if (pack->function == mouse)
        {
            if (rect.intersects(sf::Rect<float>(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, 1, 1)))
            {
                tuch = true;
            }
            int x = sf::Mouse::getPosition().x;
            int y = sf::Mouse::getPosition().y;
            pack->sprite->setPosition(x, y);
            if (tuch)
            {
                pack->sprite->setColor(sf::Color::Red);
            }
            else
            {
                pack->sprite->setColor(sf::Color::Green);
            }
            //pack->sprite->move(1, 1);
            /*for (auto i : m_sprites)
            {
                if (pack != i)
                {
                    if (i->sprite->getGlobalBounds().intersects(pack->sprite->getGlobalBounds()))
                    {

                    }
                }
            }*/
        }
        if (pack->function == live)
        {
            pack->sprite->setScale((pack->scale*sin((val+90) / FLASH_SPEED_FACTOR)), pack->scale);
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                mainPerson.addLive(pack->value);
                pack->deleteFlag = true;
                del_pack = true;
            }
        }
        if (pack->function == end)
        {
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                level.end = true;
            }
        }
        for (auto& pen : pencil)
        {
            if (pen.get_rectangle().intersects(pack->sprite->getGlobalBounds()))
            {
                del_pen = true;
                //break;
            }
        }
        if (del_pen)
        {
            pencil.erase(std::remove_if(
                pencil.begin(),
                pencil.end(),
                [pack](auto pen) {return pen.get_rectangle().intersects(pack->sprite->getGlobalBounds()); }));
        }
        del_pen = false;
        
    }
    mainPerson.setPencil(pencil);
    if (del_pack)
    {
        m_sprites.erase(std::remove_if(
            m_sprites.begin(),
            m_sprites.end(),
            [](auto x) {return x->deleteFlag; }));
    }
    
/*
    if (no_col == true)
    {
        col.left_enable = true;
        col.right_enable = true;
        col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
    }*/
    score->setString("Points: " + std::to_string(*points));
    level.score = *points;
    level.live = mainPerson.getLive();
    level.pencil = mainPerson.getNbPencil();
    return level;
}

std::vector<std::shared_ptr<sf::Drawable>> Interactives::get_drawables(void)
{
    std::vector<std::shared_ptr<sf::Drawable>> drawable;
    for (auto n : m_drawable)
    {
        drawable.push_back(n);
    }
    for (auto n : m_sprites)
    {
        drawable.push_back(n->sprite);
    }
    return drawable;
}