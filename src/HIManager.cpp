//
// Created by samuel on 31.03.16.
//

#include "HIManager.h"

void HIManager::process(void) {

		bool FlagUse = 1;

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
							FlagUse = 0;
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
                    if (event.key.code == sf::Keyboard::Up)
                    {
                        HIEvent_sig(HIEvent::FAST_UP);
                        FlagUse = 0;
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
			FlagUse = 0;
		};
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
            HIEvent_sig(HIEvent::GO_RIGHT);
			FlagUse = 0;
		};
        
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			HIEvent_sig(HIEvent::GO_UP);
			FlagUse = 0;
		};
	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			HIEvent_sig(HIEvent::GO_DOWN);
			FlagUse = 0;
		};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            HIEvent_sig(HIEvent::JUMP);
			FlagUse = 0;
        };
        
		if (FlagUse)
		{
			HIEvent_sig(HIEvent::DEFAULT);
		};
}

