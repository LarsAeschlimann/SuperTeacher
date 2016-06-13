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
using namespace std;


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
    
    Ground ground(resource, "level");
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

    window.setFramerateLimit(50);
    HIManager user_input = {&window};


    user_input.HIEvent_sig.connect([&window](HIEvent event)->void{
        switch(event) {
            case HIEvent::CLOSE:
                window.close();
				break;
            default:
                break;
        }
    });
    

	
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
    
    while(window.isOpen()){


        user_input.process();

        character.write_collision(interact.update(character,score,ground_level*BLOCK_PXSIZE));
        character.update();

        window.clear(sf::Color::Blue);
        view.process(character.get_rectangle());
        window.setView(view.GetView());
        
        auto tmp_time = Timer::get_time_s();
        timetext->setString("Time: " + to_string(tmp_time) + " sec");
        pencil->setString("Pencils: " + to_string(character.getNbPencil()));
        live->setString("Lives: " + to_string(character.getLive()));
        if (character.getLive() <= 0)
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

    LOG(info) << "Good bye, end of main process";
    return 0;
}
