#include <SFML/Graphics.hpp>
#include "header/ColorManager.h"
#include "header/Tile.h"
#include "header/GAME_BOARD.h"
#include "header/Menu.h"
#include "header/MENU_MANAGER.h"


Menu::Menu(std::vector<std::string> menuOptions){
    this->menuOptions = menuOptions;
    float startingPosition = 273.f;
    for(int i = 0; i < menuOptions.size(); i++){
        menuOptionText.push_back(sf::Text(arial));
        menuOptionText[i].setString(menuOptions[i]);
        menuOptionText[i].setFillColor(sf::Color::White);
        menuOptionText[i].setCharacterSize(50);
        menuOptionText[i].setPosition(sf::Vector2f(221.f, startingPosition));
        startingPosition += 50.0;
    }

}
void Menu::draw(sf::RenderWindow* window){
    window->draw(MENU_BACKGROUND);
    widget.setPosition(sf::Vector2f(221.f - 53, 273.f + (50 * currentPosition)));
    for(int i = 0; i < menuOptionText.size(); i++){
        window->draw(menuOptionText[i]);
    }
    window->draw(widget);
}
void Menu::menuUp(){
    if(currentPosition != 0){
        currentPosition--;
    }
    else{
        currentPosition = menuOptionText.size() - 1;
    }
}
void Menu::menuDown(){
    currentPosition = ((currentPosition + 1) % menuOptionText.size());
}

int Menu::getCurrentPosition(){
    return this->currentPosition;
}

std::vector<sf::Text> Menu::getMenuOptionText(){
    return this->menuOptionText;
}


void StartMenu::execute(){
    if(this->getCurrentPosition() == 0)
    game->setCurrentMenu(mM->getScoreMenu());
    gameBoard->instantiateGameBoard();
}
void StartMenu::setGameBoard(GameBoard* gameBoard){
    this->gameBoard = gameBoard;
}
StartMenu::StartMenu(std::vector<std::string> menuOptions) : Menu( menuOptions){

}

void ScoreMenu::execute(){
    if(this->getCurrentPosition() == 0)
    
    gameBoard->instantiateGameBoard();
}  

void ScoreMenu::setGameBoard(GameBoard* gameBoard){
    this->gameBoard = gameBoard;
}

ScoreMenu::ScoreMenu(std::vector<std::string> menuOptions) : Menu( menuOptions){

}

void ScoreMenu::draw(sf::RenderWindow* window) {
    window->draw(MENU_BACKGROUND);
    widget.setPosition(sf::Vector2f(221.f - 53, 273.f + (50 * this->getCurrentPosition())));
    for(int i = 0; i < this->getMenuOptionText().size(); i++){
        window->draw(this->getMenuOptionText()[i]);
    }
    window->draw(widget);

    sf::Text scoreText(arial,("Score: " + std::to_string(this->gameBoard->getScore())), 50);
    scoreText.setPosition(sf::Vector2f(221.f , 200.f));
    window->draw(scoreText);
}


Menu* MenuManager::getStartMenu(){
    return this->startMenu;
}

Menu* MenuManager::getScoreMenu(){
    return this->scoreMenu;
}

void MenuManager::setStartMenu(Menu* startMenu){
    this->startMenu = startMenu;
}

void MenuManager::setScoreMenu(Menu* scoreMenu){
    this->scoreMenu = scoreMenu;
}

