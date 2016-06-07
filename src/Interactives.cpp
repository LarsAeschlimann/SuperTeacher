//
//  Interactives.cpp
//  SuperTeacher
//
//  Created by Etienne Houriet on 06.06.16.
//
//

#include "Interactives.h"
#include "Constants.h"
#include <algorithm>

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
    return convert_val;
}

Interactives::Interactives(std::shared_ptr<ResourceManager> resource, std::string level_name) {

    m_resource = resource;

    auto level = m_resource->get_json("levels/" + level_name + ".json");

    auto objects = (*level)["interactive"];
    
    for (auto object : objects) {
        std::string name = object["image"];
        auto texture = m_resource->get_texture("graphics/" + name + ".png");
        auto temp = std::make_shared<sf::Sprite>();
        auto sprite = std::make_shared<act_pack>();
        temp->setTexture(*texture);
        int x = object["x"];
        int y = object["y"];
        temp->setScale(object["size"], object["size"]);
        temp->move(x*BLOCK_PXSIZE, y*BLOCK_PXSIZE-temp->getGlobalBounds().height);
        sprite->sprite = temp;
        sprite->function = string_conv(object["function"]);
        if (sprite->function == mob || sprite->function == bonus || sprite->function == charge)
        {
            sprite->value = object["value"];
        }
        sprite->use = false;
        sprite->deleteFlag = false;
        m_sprites.push_back(sprite);
        //add_drawable(sprite->sprite);
    }
}


colision Interactives::update( sf::FloatRect rect, std::shared_ptr<sf::Text> score)
{
    colision col;
    static float val = 0;
    val += 0.2;
    static int points = 0;
    bool no_col = true;
    bool del = false;
    //void *supp = NULL;
    for (auto& pack : m_sprites)
    {
        if (pack->function == platform)
        {
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {

                if ((rect.top +rect.height) <= pack->sprite->getGlobalBounds().top+20)
                {
                    col.walk_level = pack->sprite->getGlobalBounds().top-rect.height+1;
                }
                else if (rect.left + rect.width / 2 >= pack->sprite->getGlobalBounds().left + pack->sprite->getGlobalBounds().width / 2)
                {
                    col.left_enable = false;
                    col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
                }
                else
                {
                    col.right_enable = false;
                    col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
                }
                no_col = false;
            }
        }
        if (pack->function == bonus)
        {
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                //if (pack->use == false)
                //{
                    //auto texture = m_resource->get_texture("graphics/interactives/invisible.png");
                    //pack->sprite->setTexture(*texture);
                    points+=pack->value;
                    pack->deleteFlag = true;
                    del = true;
                    //supp = (&pack - &m_sprites[0]);
                    //supp = pack.use_count();
                    //supp = &pack;
                    //pack._Decref();
                    //delete &pack;
                    //pack = m_sprites.erase(pack);
                //}
                //break;
                //pack->use = true;
            }

        }
        if (pack->function == charge)
        {
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                if (pack->use == false)
                {
                    auto texture = m_resource->get_texture("graphics/interactives/invisible.png");
                    pack->sprite->setTexture(*texture);
                    points += pack->value;
                }
                pack->use = true;
            }

        }
        if (pack->function == mob)
        {
            pack->sprite->move(cos(val / 5) * 10, 0);
            if (rect.intersects(pack->sprite->getGlobalBounds()))
            {
                if (pack->use == false)
                {
                    points-=pack->value;
                }
                pack->use = true;
            }
            else
            {
                pack->use = false;
            }
        }
    }
    /*if (supp != NULL)
    {
        m_sprites.erase(supp);
    }*/
    if (del)
    {
        m_sprites.erase(std::remove_if(
            m_sprites.begin(),
            m_sprites.end(),
            [](auto x) {return x->deleteFlag; }));
    }

    if (no_col==true)
    {
        col.left_enable = true;
        col.right_enable = true;
        col.walk_level = 658 - (BLOCK_PXSIZE * ((SCREEN_Y_BLOCKS)-16));
    }
    score->setString("Points: " + std::to_string(points));
    return col;
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