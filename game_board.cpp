#include <SFML/Graphics.hpp>
#include "header/ColorManager.h"
#include "header/Tile.h"
#include "header/GAME_BOARD.h"

        
void GameBoard::draw(sf::RenderWindow* window){
    GAME_BACKGROUND.setPosition(sf::Vector2f((768), (237)));
    window->draw(GAME_BACKGROUND);
    for(unsigned int i = 0; i < gameBoard.size(); i++){
        for(unsigned int j = 0; j < gameBoard[i].size(); j++){
            if(gameBoard[i][j].isActive()){
                gameBoard[i][j].draw(window);
                
            }
        }
    }
    window->draw(cursor);
    scoreText.setString("Score: " + std::to_string(gameScore));
    window->draw(scoreText);
}


void GameBoard::instantiateGameBoard(){
    scoreText.setPosition(sf::Vector2f(767.f, 155.f));
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setCharacterSize(80);
    gameScore = 0;
    gameLost = false;
    for(unsigned int i = 0; i < 6; i++){
        for(unsigned int j = 0; j < gameBoard[i].size(); j++){
            gameBoard[i][j].setActive(true);
            
            
        }
    }
    for(unsigned int i = 0; i < gameBoard.size(); i++){
        for(unsigned int j = 0; j < gameBoard[i].size(); j++){
            gameBoard[i][j].setFillColor(cM.getRandomColor());
            gameBoard[i][j].updatePosition(i, j);
            
        }
    }
    for(unsigned int i = 6; i < gameBoard.size(); i++){
        for(unsigned int j = 0; j < gameBoard[i].size(); j++){
            gameBoard[i][j].setActive(false);
        }
    }
    cursor.setPosition(sf::Vector2f((768 + (xCrdCursor * 64)), (940 - (yCrdCursor*64))));
}
void GameBoard::upKey(){
    if(yCrdCursor != 11){
        yCrdCursor++;
        updateCursor();
    }
}
void GameBoard::downKey(){
    if(yCrdCursor != 0){
        yCrdCursor--;
        updateCursor();
}}
void GameBoard::leftKey(){
    if(xCrdCursor != 0){
        xCrdCursor--;
        updateCursor();
    }}
void GameBoard::rightKey(){
    if(xCrdCursor != 4){
        xCrdCursor++;
        updateCursor();
    }
}
void GameBoard::updateCursor(){
    cursor.setPosition(sf::Vector2f((768 + (xCrdCursor * 64)), (1080 - 140 - (yCrdCursor*64))));
    
}

void GameBoard::switchTiles(){
    if(gameBoard[yCrdCursor][xCrdCursor].isActive() &&gameBoard[yCrdCursor][xCrdCursor + 1].isActive()){
        sf::Color color = gameBoard[yCrdCursor][xCrdCursor].getFillColor();
        gameBoard[yCrdCursor][xCrdCursor].setFillColor(gameBoard[yCrdCursor][xCrdCursor + 1].getFillColor());
        gameBoard[yCrdCursor][xCrdCursor + 1].setFillColor(color);
    }
    else if (gameBoard[yCrdCursor][xCrdCursor].isActive() && !(gameBoard[yCrdCursor][xCrdCursor + 1].isActive())){
        gameBoard[yCrdCursor][xCrdCursor].setActive(false);
        gameBoard[yCrdCursor][xCrdCursor + 1].setActive(true);
        gameBoard[yCrdCursor][xCrdCursor + 1].setFillColor(gameBoard[yCrdCursor][xCrdCursor].getFillColor());
    }
    else if (!(gameBoard[yCrdCursor][xCrdCursor].isActive()) && (gameBoard[yCrdCursor][xCrdCursor + 1].isActive())){
        gameBoard[yCrdCursor][xCrdCursor + 1].setActive(false);
        gameBoard[yCrdCursor][xCrdCursor].setActive(true);
        gameBoard[yCrdCursor][xCrdCursor].setFillColor(gameBoard[yCrdCursor][xCrdCursor +1].getFillColor());
    }
}

void GameBoard::emitScore() {
    std::vector<DestroyedTileCoordinate> destroyedTileCoordinates;
    
    for(unsigned int j = 0; j < gameBoard.size(); j++) {
        for(unsigned int i = 1; i < (gameBoard[0].size() - 1); i++) {
            if(gameBoard[j][i].isActive() && gameBoard[j][i -1].isActive() && gameBoard[j][i +1].isActive()){
            if(gameBoard[j][i].getFillColor().toInteger() == gameBoard[j][i-1].getFillColor().toInteger() &&
            gameBoard[j][i].getFillColor().toInteger() == gameBoard[j][i+1].getFillColor().toInteger()) {
                
                    destroyedTileCoordinates.push_back(DestroyedTileCoordinate(j, i-1));

                destroyedTileCoordinates.push_back(DestroyedTileCoordinate(j, i));
                if(j < gameBoard.size() - 1) { // Verhindert j+1 >= size
                    destroyedTileCoordinates.push_back(DestroyedTileCoordinate(j, i+1));
                }
            }
        }}
    }

    for(unsigned int j = 1; j < gameBoard.size() -1; j++) {
        for(unsigned int i = 0; i < (gameBoard[0].size()); i++) {
            if(gameBoard[j][i].isActive() && gameBoard[j-1][i].isActive() && gameBoard[j+1][i].isActive()){
            if(gameBoard[j][i].getFillColor().toInteger() == gameBoard[j -1][i].getFillColor().toInteger() &&
            gameBoard[j][i].getFillColor().toInteger() == gameBoard[j + 1][i].getFillColor().toInteger()) {
                
                destroyedTileCoordinates.push_back(DestroyedTileCoordinate(j -1, i));

                destroyedTileCoordinates.push_back(DestroyedTileCoordinate(j, i));
                if(j < gameBoard.size() - 1) { // Verhindert j+1 >= size
                    destroyedTileCoordinates.push_back(DestroyedTileCoordinate(j+1, i));
                }
            }
        }
    }
}
    for (DestroyedTileCoordinate dTc : destroyedTileCoordinates) {
        gameBoard[dTc.i][dTc.j].setActive(false);
        gameScore++;
    }
}
        
bool GameBoard::gravity(float elapsedTime){
    if(elapsedTime > 1){
        for(unsigned int i = 1; i < gameBoard.size(); i++) {
            for(unsigned int j = 0; j < gameBoard[0].size(); j++) {
                if(!gameBoard[i -1][j].isActive() && gameBoard[i][j].isActive()){
                    gameBoard[i][j].setActive(false);
                    gameBoard[i-1][j].setActive(true);
                    gameBoard[i-1][j].setFillColor(gameBoard[i][j].getFillColor());
                }
            }
        }
        return true;
    }
    return false;

    }
    
bool GameBoard::pushNewLine(float elapsedTime){
    if(elapsedTime > 5){
        if(checkIfTerminal()){
            gameLost=true;
        }
        else{
            for(int i = 0; i < gameBoard[11].size(); i++){
                gameBoard[11][i].setFillColor(cM.getRandomColor());
                gameBoard[11][i].setActive(true);
            }
        }
        return true;
    }
    return false;

}
bool GameBoard::checkIfTerminal(){
    for(unsigned int i = 0; i < gameBoard[11].size(); i++){
        if(gameBoard[11][i].isActive()){
            return true;
        }
    }
    return false;
}

bool GameBoard::isLost(){ return this->gameLost;}
int GameBoard::getScore(){ return this->gameScore;}
void GameBoard::setLost(bool gameLost){this->gameLost = gameLost;}
void GameBoard::setScore(int score){this->gameScore = score;}
