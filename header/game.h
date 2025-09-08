
#ifndef game_h
#define game_h
#include <SFML/Graphics.hpp>
#include "ColorManager.h"
#include "Tile.h"
#include "GAME_BOARD.h"
#include "Menu.h"



void activeGameEventHandling(GameBoard* gameBoard, bool pressed);
void menuEventHandling(Menu* menu, bool pressed);
class Game{
    public:
        sf::RenderWindow * window;
        GameBoard * gameBoard;
        Menu* currentMenu;
        void run();
        void setCurrentMenu(Menu* currentMenu);
};
#endif