#pragma once

#include "Object.h"

#include <string>
#include <memory>
#include "ResourceManager.h"
#include "HIManager.h"
#include "Pencil.h"


    typedef struct {
    bool right_enable;
    bool left_enable;
    int walk_level;
    int x_move;
    }colision;

class Character: public Object {
public:
    void process_event(HIEvent event);
    void update(void);
    Character(std::shared_ptr<ResourceManager> ressource, std::string level_name,int GroundLevel);
    std::vector<std::shared_ptr<sf::Drawable>> get_drawables(void);
    int getCharacterLevel(void);
    sf::FloatRect get_rectangle(void);
    void write_collision(colision coll);
    int getNbPencil(void);
    void addPencil(int nb);
    std::vector<Pencil> getPencil(void);
    void setPencil(std::vector<Pencil> new_pencils);
    void addLive(int val);
    int getLive(void);

private:
    std::shared_ptr<ResourceManager> m_resource;
    std::shared_ptr<sf::Sprite> m_animation;
    std::vector<Pencil> m_pencils;
    colision colisi;
    int m_nb_pencils;
    int m_live;
    int jumpLevel;
    int MINLEVEL;
    bool flag1;
};
