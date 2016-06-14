#include "Menu.h"
#include "Interactives.h"
#include "Path.h"
#include "Level.h"

Menu::Menu(std::shared_ptr<ResourceManager> resource)
{

    song = resource->get_music(SONG_MENU);
    song->setLoop(true);
    song->play();
    auto menu = resource->get_json("levels/menu.json");

    for (auto but : (*menu)["button"])
    {
        auto button = std::make_shared<Button>();
        std::string source_1 = but["image_off"];
        std::string source_2 = but["image_on"];
        auto sprite = std::make_shared<sf::Sprite>();
        button->off = resource->get_texture("graphics/" + source_1 + ".png");
        button->on = resource->get_texture("graphics/" + source_2 + ".png");
        sprite->setTexture(*button->off);
        button->sprite = sprite;
        std::string name = but["name"];
        std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>(name, *resource->get_font(MATHLETE), 100);
        int x = but["x"];
        int y = but["y"];
        x *= BLOCK_PXSIZE;
        x += (int)((float)SCREEN_X_PXSIZE / 2-sprite->getGlobalBounds().width/2);
        y *= BLOCK_PXSIZE;
        y += (int)((float)SCREEN_Y_PXSIZE / 2-sprite->getGlobalBounds().height/2);
        button->sprite->setPosition((float)x, (float)y);
        text->setPosition(x+sprite->getGlobalBounds().width/2-text->getGlobalBounds().width/2,
            y+ sprite->getGlobalBounds().height / 2 - text->getGlobalBounds().height);

        std::string function = but["function"];
        button->function = function;
        button->text = text;
        buttons.push_back(button);
    }
}

void Menu::update(level_str level_info, sf::RenderWindow* window)
{
    for (auto button : buttons)
    {
        if (button->function == "score")
        {
            if (level_info.live > 0)
            {
                button->text->setString("Score: " + std::to_string((int)level_info.score));
            }
            else
            {
                button->text->setString("Game Over");
            }
        }
        if (button->sprite->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window).x*SCREEN_X_PXSIZE/window->getSize().x,
            sf::Mouse::getPosition(*window).y*SCREEN_Y_PXSIZE / window->getSize().y)))
        {
            button->sprite->setTexture(*button->on);
        }
        else
        {
            button->sprite->setTexture(*button->off);
        }
        window->draw(*button->sprite);
        window->draw(*button->text);
    }
}

void Menu::process_event_menu(HIEvent events, std::shared_ptr<const json> config, sf::RenderWindow * window, level_str * level_info)
{
    static int level_num = 0;
    switch (events) {
    case HIEvent::MOUSE_DOWN:
        for (auto button : buttons)
        {
            if (button->sprite->getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window).x*SCREEN_X_PXSIZE / window->getSize().x,
                sf::Mouse::getPosition(*window).y*SCREEN_Y_PXSIZE / window->getSize().y)))
            {
                if (button->function == "play")
                {
                    std::string temp = ((*config)["level_names"][level_num]);
                    level_info->name = temp;
                    level_info->end = false;
                    level_str temp_level = *level_info;
                    song->pause();
                    if (level_execute(&temp_level, window))
                    {
                        *level_info = temp_level;
                        level_num++;
                        if (level_num >= ((int)(*config)["level_number"]))
                        {
                            level_num = 0;
                        }
                    }
                    else
                    {
                        if (temp_level.live <= 0)
                        {
                            level_num = 0;
                            level_info->score = 0;
                            level_info->live = 0;
                        }
                    }
                    song->play();
                }
                if (button->function == "restart")
                {
                    level_num = 0;
                    *level_info = { false,0,0,0,(*config)["level_names"][level_num] };
                    song->pause();
                    level_execute(level_info, window);
                    song->play();
                    if (level_info->live > 0)
                    {
                        level_num++;
                        if (level_num >= ((int)(*config)["level_number"]))
                        {
                            level_num = 0;
                        }
                    }
                }
                if (button->function == "quit")
                {
                    window->close();
                }
            }
        }
        break;
        /*case HIEvent::GO_UP:
        view.move(0, -1);
        break;
        case HIEvent::GO_DOWN:
        view.move(0, 1);
        break;
        case HIEvent::GO_LEFT:
        view.move(-1, 0);
        break;
        case HIEvent::GO_RIGHT:
        view.move(1, 0);
        break;*/
    default:
        break;
    }
}

