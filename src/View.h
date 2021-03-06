#pragma once
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Object.h"

class View
{
public:
    View(sf::FloatRect PlaySpaceInit);
    void process(sf::FloatRect CenterObj);
    sf::View GetView(void) { return view; };
    void SetSize(sf::Vector2f size) { view.setSize(size); };

private:
    sf::View view;
    sf::FloatRect PlaySpace;
};