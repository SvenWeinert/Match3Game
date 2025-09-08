#pragma once
#include <SFML/Graphics.hpp>
#include "ColorManager.h"
#include "Tile.h"


static sf::Texture GAME_BACKGROUND_TEXTURE("resources/background.png", false, sf::IntRect({0, 0}, {384, 768}));
static sf::Sprite GAME_BACKGROUND(GAME_BACKGROUND_TEXTURE);

class GameBoard{
    private:
        std::vector<std::vector<Tile>> gameBoard;
        unsigned int xCrdCursor = 0;
        unsigned int yCrdCursor = 0;
        ColorManager cM;
        sf::Sprite cursor;
        bool gameLost = true;
        unsigned int gameScore = 0;
        sf::Text scoreText;
        
    
    public:
        GameBoard(sf::Sprite cursor, sf::Text scoreText) : gameBoard(12, std::vector<Tile>(6)), cM(), cursor(cursor), scoreText(scoreText){
               
        }
    void draw(sf::RenderWindow* window);
    void instantiateGameBoard();
    void upKey();
    void downKey();
    void leftKey();
    void rightKey();
    void updateCursor();
    void switchTiles();
    void emitScore();
    bool gravity(float elapsedTime);
    bool pushNewLine(float elapsedTime);
    bool checkIfTerminal();


    bool isLost();
    int getScore();


    void setLost(bool gameLost);
    void setScore(int score);
};