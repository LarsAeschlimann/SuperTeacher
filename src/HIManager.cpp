//
// Created by samuel on 31.03.16.
//

#include "HIManager.h"

void HIManager::process(void) {


        while(window->pollEvent(event)){

            switch(event.type){

                // Window manager request a close
                case sf::Event::Closed:
                    HIEvent_sig(HIEvent::CLOSE);
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        /*case sf::Keyboard::Right:
                            HIEvent_sig(HIEvent::GO_RIGHT);
                            break;*/
                        case sf::Keyboard::Up:
							HIEvent_sig(HIEvent::FAST_DOWN);
							break;
                        case sf::Keyboard::Down:
                            HIEvent_sig(HIEvent::DOWN_DOWN);
                            break;
						case sf::Keyboard::Escape:
                            HIEvent_sig(HIEvent::CLOSE);
							break;
                        case sf::Keyboard::T:
                            HIEvent_sig(HIEvent::THROW);
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    switch (event.key.code) {
                    case sf::Keyboard::Up:
                        HIEvent_sig(HIEvent::FAST_UP);
                        break;
                    case sf::Keyboard::Down:
                        HIEvent_sig(HIEvent::DOWN_UP);
                        break;
                    case sf::Keyboard::Right:
                        HIEvent_sig(HIEvent::KEY_UP);
                        break;
                    case sf::Keyboard::Left:
                        HIEvent_sig(HIEvent::KEY_UP);
                        break;
                    default:
                        break;

                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    HIEvent_sig(HIEvent::MOUSE_DOWN);
                    break;
                default:
                    break;
            }
        }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
            
			HIEvent_sig(HIEvent::GO_LEFT);
		};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
            HIEvent_sig(HIEvent::GO_RIGHT);
		};
        
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			HIEvent_sig(HIEvent::GO_UP);
		};
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			HIEvent_sig(HIEvent::GO_DOWN);
		};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            HIEvent_sig(HIEvent::JUMP);
        };
}

