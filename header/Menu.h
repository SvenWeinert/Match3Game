#pragma once
#include <SFML/Graphics.hpp>
#include "ColorManager.h"
#include "Tile.h"
#include "GAME_BOARD.h"
#include "MENU_MANAGER.h"
#include "game.h"

class Game;

static sf::Texture widgetTexture("resources/widget.png", false, sf::IntRect({0, 0}, {53, 41}));
static sf::Sprite widget(widgetTexture);
static sf::Texture MENU_BACKGROUND_TEXTURE("resources/menuScreen.png", false, sf::IntRect({0, 0}, {1920, 1080}));
static sf::Sprite MENU_BACKGROUND(MENU_BACKGROUND_TEXTURE);



const sf::Font arial("arial.ttf");

enum class DIFFICULTY{
    EASY,
    NORMAL,
    HARD
};


class Menu{
    private:
        std::string name;
        std::vector<std::string> menuOptions;
        int currentPosition = 0;
        std::vector<sf::Text> menuOptionText;
    public:
        Game* game;
        MenuManager* mM;
        Menu(std::vector<std::string> menuOptions);
        virtual void draw(sf::RenderWindow* window);
        void menuUp();
        void menuDown();

        virtual void execute() = 0;

        int getCurrentPosition();
        std::vector<sf::Text> getMenuOptionText();

};



class StartMenu: public Menu{
    private:
        GameBoard* gameBoard;
    
    public:
    void execute();
    void setGameBoard(GameBoard* gameBoard);
    StartMenu(std::vector<std::string> menuOptions);
};

class ScoreMenu: public Menu{
    private: GameBoard* gameBoard;

    public:
    void execute();
    void draw (sf::RenderWindow* window) override;
    void setGameBoard(GameBoard* gameBoard);
    ScoreMenu(std::vector<std::string> menuOptions);

};

