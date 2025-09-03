#include "header/ColorManager.h"

ColorManager::ColorManager() {
    std::srand(std::time(0));
    red = sf::Color(255, 0, 97); 
    blue = sf::Color(0, 195, 255); 
    green = sf::Color(17, 230, 45); 
    yellow = sf::Color(255, 188, 45); 
}

sf::Color ColorManager::getRandomColor() {
    int randomInt = std::rand() % 4;

    switch(randomInt) {
        case 0: return red;
        case 1: return blue;
        case 2: return green;
        case 3: return yellow;
        default: return red;
    }
}