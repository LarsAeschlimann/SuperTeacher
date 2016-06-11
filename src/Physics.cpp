//
// Created by samuel on 01.04.16.
//

#include "Physics.h"

#include <cmath>
#include <chrono>

auto startup = std::chrono::high_resolution_clock::now();

    
uint64_t Timer::get_time_ms(){
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now-startup).count() ;
}


uint64_t Timer::get_time_s(){

    return get_time_ms()/1000;
}

void jump_manager(std::shared_ptr<sf::Sprite> sprite, float GroundLevel,int vitesseInit)
{
    static float startup = 0;
	static int vitesse0;
	static float posy_m_un;
    float time_now = 0;
	float posy;

	if (sprite->getPosition().y >= GroundLevel)
	{
        startup = Timer::get_time_ms() / 1000.0;
		vitesse0 = vitesseInit;
		posy_m_un = 0;
	}

    time_now = Timer::get_time_ms() / 1000.0;

    float delta_t = time_now - startup;

    posy = (
            (float)delta_t + 0.001
           ) * vitesse0 * METER
        + (
           std::pow((float)delta_t, 2)*GRAVITY
        ) * METER / 2.0;
    
    
	if ((posy- posy_m_un)+ sprite->getPosition().y >= GroundLevel)
    {
        posy = GroundLevel - (sprite->getPosition().y - posy_m_un)+1;
    }
	sprite->move(0, (posy - posy_m_un));
	posy_m_un = posy;
}
