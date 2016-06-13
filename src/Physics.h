#pragma once

#include <array>
#include <bitset>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "HIManager.h"
#include "Logs.h"
#include <ctime>
#include <cstdint>


class Timer{
public:

    static uint64_t get_time_ms();
    static uint64_t get_time_s();
    
private:
    
};
float jump_level_manager(float);
void jump_manager(std::shared_ptr<sf::Sprite> sprite, float GroundLevel, int vitesseInit,bool ColisionFlags);
class Physics {
public:
    //Add_
private:
    std::array<std::bitset<SCREEN_X_BLOCKS>, SCREEN_Y_BLOCKS> blocks;
};
