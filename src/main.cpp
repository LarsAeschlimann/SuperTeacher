#include <iostream>
#include <memory>
#include <time.h>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
#include "Menu.h"
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

    level_str level_info = {false,0,1,0," "};
    sf::View view;
    view.setCenter(sf::Vector2f(SCREEN_X_PXSIZE / 2, SCREEN_Y_PXSIZE / 2));
    view.setSize(sf::Vector2f(SCREEN_X_PXSIZE, SCREEN_Y_PXSIZE));
    auto main_menu = Menu(resource);

    HIManager user_input = { &window };
    user_input.HIEvent_sig.connect([&window,&level_info,&view](HIEvent event)->void{
        switch(event) {
            case HIEvent::CLOSE:
                window.close();
				break;
            default:
                break;
        }
    });
    user_input.HIEvent_sig.connect([&main_menu, &window, &config,&level_info](HIEvent event)->void {
        main_menu.process_event_menu(event, config, &window,&level_info); });

    while (window.isOpen())
    {
        window.clear();
        main_menu.update(level_info,&window);
        window.setView(view);
        window.display();
        user_input.process();

    }
    
    LOG(info) << "Good bye, end of main process";
    return 0;
}