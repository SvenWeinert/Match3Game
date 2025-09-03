#include <iostream>
#include <SFML/Graphics.hpp>
#include "header/Tile.h"

Tile::Tile():active(false), rectangle(sf::Vector2f(64.f, 64.f)){};
void Tile::draw(sf::RenderWindow* window){
    window->draw(rectangle);
    }
void Tile::setActive(bool active){this->active = active;}
bool Tile::isActive(){ return this->active;}

void Tile::setFillColor(const sf::Color& color) {
    rectangle.setFillColor(color);
    }
sf::Color Tile::getFillColor(){
    return rectangle.getFillColor();
    }

void Tile::updatePosition(const unsigned int i, const unsigned int j){
    rectangle.setPosition(sf::Vector2f((768 + (j * 64)), (1080 - 140 - (i*64))));
    }
