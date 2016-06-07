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

float jump_level_manager(float time)
{
    if (time<=800) {
        return 10;
    }
    else
    {
        return 4;
    }
}

void throw_manager(std::shared_ptr<sf::Sprite> sprite, float posx, float posy,bool enable)//function to throw things
{
    static float time = Timer::get_time_ms();
    float position_y = 0;
    if(enable)
    {
        if((Timer::get_time_ms()-time)<=2000)
        {
            position_y = GRAVITY*(Timer::get_time_ms()-time)/2000;
            sprite->move(30,position_y);
            sprite->rotate(1);
        }
        else
        {
            time = Timer::get_time_ms();
            sprite->setPosition(posx+MISSILE_OFFSET_X, posy+MISSILE_OFFSET_Y);
            sprite->setRotation(200);
        }
    }
    else
    {
        sprite->setPosition(posx+MISSILE_OFFSET_X, posy+MISSILE_OFFSET_Y);
        sprite->setRotation(200);
    }
}


void jump_manager(std::shared_ptr<sf::Sprite> sprite, float GroundLevel,int vitesseInit,bool ColisionFlag)
{
    static float startup = 0;
	static int vitesse0;
	static float posy_m_un;
    float time_now = 0;
	float posy;

	if (sprite->getPosition().y >= GroundLevel || ColisionFlag)
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
		posy = GroundLevel-(sprite->getPosition().y-posy_m_un);
	sprite->move(0, (posy - posy_m_un));
	posy_m_un = posy;
}
