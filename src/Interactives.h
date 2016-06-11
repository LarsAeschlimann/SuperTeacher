#pragma once

#include "Object.h"

#include <string>
#include <memory>
#include "ResourceManager.h"
#include "Character.h"
#include "Text.h"

typedef enum
{
    nothing,
    platform,
    bonus,
    mob,
    charge,
    mouse,
    live,
    end
}function_enum;

typedef struct
{
    bool end;
    int score;
    int live;
    int pencil;
    std::string name;
}level_str;

typedef struct
{
    std::shared_ptr<sf::Sprite> sprite;
    function_enum function;
    bool use;
    bool deleteFlag;
    int value;
    float scale;
    sf::FloatRect Transform;
}act_pack;

class Interactives : public Object {
public:
    Interactives(std::shared_ptr<ResourceManager> ressource, std::string level_name);
    level_str update(Character& mainPerson, std::shared_ptr<sf::Text> score, int GroundLevel,colision* col,int *points);
    //colision update( sf::FloatRect rect, std::shared_ptr<sf::Text> score);
    std::vector<std::shared_ptr<sf::Drawable>> get_drawables(void);
private:
    std::shared_ptr<ResourceManager> m_resource;
    std::vector<std::shared_ptr<act_pack>> m_sprites;
    float val;
};
