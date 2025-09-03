#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

class ColorManager {
private:
    sf::Color red;
    sf::Color blue;
    sf::Color green;
    sf::Color yellow;
    
public:
    ColorManager();
    sf::Color getRandomColor();
};