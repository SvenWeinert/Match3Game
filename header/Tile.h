#pragma once
#include <SFML/Graphics.hpp>

struct DestroyedTileCoordinate {
    unsigned int i;
    unsigned int j;
    
    DestroyedTileCoordinate(int i, int j) : i(i), j(j) {}
};

class Tile{
    private:
        bool active = false;
        sf::RectangleShape rectangle;
    public:
        Tile();
        void setActive(bool active);
        bool isActive();
        void setFillColor(const sf::Color& color);
        sf::Color getFillColor();
        void updatePosition(const unsigned int i, const unsigned int j);
        void draw(sf::RenderWindow* window);
        

};