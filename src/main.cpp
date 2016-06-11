#include <iostream>
#include <memory>
#include <time.h>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <clock.hpp>

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
#include "Level.h"
using namespace std;

typedef struct
{
    shared_ptr<sf::Sprite> sprite;
    shared_ptr<sf::Text> text;
    string function;
}Button;


int main(int argc, char *argv[]) {

    log_init();

    LOG(info)  << "Superteacher is starting";
    LOG(debug) << "SRC Directory: " << _SRC_DIR;
    LOG(debug) << "Install Prefix: " << _INSTALL_PREFIX;

    LOG(info) << "Opening window";
    LOG(debug) << "Window size: " << SCREEN_X_PXSIZE << "x" << SCREEN_Y_PXSIZE;


    auto resource = make_shared<ResourceManager>();
    auto config = resource->get_json("conf.json");
    auto style = sf::Style::Default;
    
    /*Ground ground(resource, "level");
    Object people = {};
    Object front_print = {};
    Interactives interact(resource, "level");
    int levelJump = 0;    
    
    auto level = resource->get_json("levels/level.json");
    View view = (sf::FloatRect(0,
        SCREEN_Y_PXSIZE-((int)(*level)["background"]["world"]["y"]) * BLOCK_PXSIZE ,
        ((int)(*level)["background"]["world"]["x"]) * BLOCK_PXSIZE,
        ((int)(*level)["background"]["world"]["y"]) * BLOCK_PXSIZE));
    Background background(resource, "level", sf::IntRect(0,
         0,
        ((int)(*level)["background"]["world"]["x"]) * BLOCK_PXSIZE,
        ((int)(*level)["background"]["world"]["y"]) * BLOCK_PXSIZE));
    auto font = resource->get_font(MATHLETE);
    auto song = resource->get_music(SONG_1);
    int ground_level = (*level)["ground"]["level"];

    Text text((string)"SuperTeacher", sf::Vector2f(-60,-25)+view.GetView().getCenter(), font);

    std::shared_ptr<sf::Text> timetext = make_shared<sf::Text>("Clock: " + to_string(Timer::get_time_ms()), *font, 100);
  
    text.Add_Text(timetext, sf::Vector2f(-1500, -25) + view.GetView().getCenter());
    */
    if((bool)(*config)["video"]["fullscreen"]){
        style = sf::Style::Fullscreen;
    }
    
    std::array<std::array<int, 18>,32> ColisionDetect = {};
    const int SOLID = 1;
    sf::RenderWindow window(
            sf::VideoMode(SCREEN_X_PXSIZE, SCREEN_Y_PXSIZE),
            "SuperTeacher",
            style
    );
//auto resource = make_shared<ResourceManager>();
 //       auto config = resource->get_json("conf.json");
 //       auto style = sf::Style::Default;

                level_str level_info = {false,0,0,0,"level"};
        auto menu = resource->get_json("levels/menu.json");
        vector<Button> buttons;

        for (auto but : (*menu)["button"])
        {
            Button button;
            string source = but["image"];
            auto sprite = make_shared<sf::Sprite>();
            auto texture = resource->get_texture("graphics/" + source + ".png");
            sprite->setTexture(*texture);
            button.sprite = sprite;
            string name = but["name"];
            shared_ptr<sf::Text> text = make_shared<sf::Text>(name, *resource->get_font(MATHLETE),100);
            text->setPosition((int)but["x"], (int)but["y"]);
            int x = but["x"];
            int y = but["y"];
            button.sprite->setPosition(x,y);

            string function = but["function"];
            button.function = function;
            button.text = text;
            buttons.push_back(button);
        }
    
    //HIManager user_input = {&window};
                sf::View view;
                view.setCenter(sf::Vector2f(SCREEN_X_PXSIZE / 2, SCREEN_Y_PXSIZE / 2));
                view.setSize(sf::Vector2f(SCREEN_X_PXSIZE, SCREEN_Y_PXSIZE));
    HIManager user_input = { &window };
    user_input.HIEvent_sig.connect([&window,&level_info,&buttons,&view](HIEvent event)->void{
        switch(event) {
            case HIEvent::CLOSE:
                window.close();
				break;
            /*case HIEvent::JUMP:
                window.setFramerateLimit(50);
                level_info = { false,0,0,0,"level" };
                level_execute(&level_info, &window);
                break;*/
            case HIEvent::MOUSE_DOWN:
                for (auto button : buttons)
                {
                    if (button.sprite->getGlobalBounds().intersects(sf::FloatRect(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y,1,1)))
                    {
                        if (button.function == "play")
                        {
                            level_info = { false,0,0,0,"level" };
                            level_execute(&level_info, &window);
                            window.setView(view);
                        }
                        if (button.function == "quit")
                        {
                            window.close();
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
    });

    while (window.isOpen())
    {
        /**/
        //window.setPosition(sf::Vector2i(0, 0));
            window.clear();
        for (auto button:buttons)
        {
            if (button.function == "score")
            {
                button.text->setString("Score: " + to_string((int)level_info.score));
            }
            window.draw(*button.sprite);
            window.draw(*button.text);
        }
    window.setView(view);
        window.display();
        user_input.process();

    }
    //window.close();
    /*
    

	
    std::shared_ptr<sf::Text> score = make_shared<sf::Text>("Points: ", *font, 50);

    text.Add_Text(score, sf::Vector2f(-900, -25) + view.GetView().getCenter());

    std::shared_ptr<sf::Text> live = make_shared<sf::Text>("Lives: ", *font, 50);

    text.Add_Text(live, sf::Vector2f(-60, -75) + view.GetView().getCenter());
    
    for (int y = 17;  y >= ground_level; y--) {
        for (int x = 0; x < 32; x++) {
            ColisionDetect[x][y] = SOLID;
        }
    }
    
    std::string gr_name = (*level)["ground"]["name"];

	
    auto character = Character(resource, "level",ground_level);
    
    character.addPencil((*level)["init"]["pencil"]);

    std::shared_ptr<sf::Text> pencil = make_shared<sf::Text>("Pencils: " + to_string(character.getNbPencil()), *font, 50);
    text.Add_Text(pencil, sf::Vector2f(-900, -75) + view.GetView().getCenter()); 

    user_input.HIEvent_sig.connect([&character](HIEvent event)->void {
        character.process_event(event);
    });
    
    
    if((bool)(*config)["audio"]){
        song->play();
    }
    colision col = { true,true,ground_level*BLOCK_PXSIZE,0 };
    
    while(window.isOpen()){


        user_input.process();
        auto level_status = interact.update(character, score, ground_level*BLOCK_PXSIZE,&col);
        character.write_collision(col);
        character.update();

        window.clear(sf::Color::Blue);
        view.process(character.get_rectangle());
        window.setView(view.GetView());
        
        auto tmp_time = Timer::get_time_s();
        timetext->setString("Time: " + to_string(tmp_time) + " sec");
        pencil->setString("Pencils: " + to_string(character.getNbPencil()));
        live->setString("Lives: " + to_string(character.getLive()));
        if (level_status.end)//(character.getLive() <= 0)
        {
            window.close();
        }
		//high_jump->setString("Jump level " + to_string(character.getCharacterLevel()));
        text.update(view.GetView().getCenter());
      
        // Dessin
    
		for (auto n : background.get_drawables())
		{
			window.draw(*n);
		}
		for (auto n : ground.get_drawables())
		{
			window.draw(*n);
		}
        for (auto n : interact.get_drawables())
        {
            window.draw(*n);
        }
		for (auto n : character.get_drawables())
		{
			window.draw(*n);
		}
		for (auto n : front_print.get_drawables())
		{
			window.draw(*n);
		}
        for (auto n : text.get_texts())
        {
            window.draw(*n);
        }
        window.display();
        window.clear();
    }
    */
    LOG(info) << "Good bye, end of main process";
    return 0;
}