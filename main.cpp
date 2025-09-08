#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "header/ColorManager.h"
#include "header/Tile.h"
#include "header/GAME_BOARD.h"
#include "header/Menu.h"
#include "header/game.h"





int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({1920, 1080}), "SFML works!", sf::Style::None, sf::State::Fullscreen);
    sf::Texture texture("image.png", false, sf::IntRect({0, 0}, {128, 64}));
    sf::Sprite cursor(texture);
    sf::Text scoreText(arial);

    std::vector<std::string> v = { "START GAME!", "HOW TO PLAY", "OPTIONS" };


    GameBoard* gameBoard = new GameBoard(cursor, scoreText);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    StartMenu* startMenu = new StartMenu(v);
    startMenu->setGameBoard(gameBoard);
    Menu* menu = startMenu;
    
    MenuManager* menuManager = new MenuManager();

    menuManager->setStartMenu(startMenu);
    ScoreMenu* scoreMenu = new ScoreMenu(v);
    scoreMenu->setGameBoard(gameBoard);
    menuManager->setScoreMenu(scoreMenu);

    menu->mM = menuManager;

    Game* game = new Game();
    game->gameBoard = gameBoard;
    game->window = window;
    menu->game = game;
    game->currentMenu = menu;

    game->run();


}