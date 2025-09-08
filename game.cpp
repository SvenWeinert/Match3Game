#include <SFML/Graphics.hpp>
#include "header/ColorManager.h"
#include "header/Tile.h"
#include "header/GAME_BOARD.h"
#include "header/Menu.h"
#include "header/game.h"
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>

const int FPS_SET = 60;


void activeGameEventHandling(GameBoard* gameBoard, bool pressed){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > 50){
            if(pressed){
            gameBoard->upKey();
            pressed = false;}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) < -50){
            if(pressed){
            gameBoard->leftKey();
            pressed = false;}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) < -50){
            if(pressed){
            gameBoard->downKey();
            pressed = false;}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || 
        sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) > 50){
            if(pressed){
            gameBoard->rightKey();
            pressed = false;}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
        sf::Joystick::isButtonPressed(0,0)){
            if(pressed){
            gameBoard->switchTiles();
            pressed = false;}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab) || 
        sf::Joystick::isButtonPressed(0,5) ||
        sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) > 80 || 
        sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) < -80) {
            if(pressed){
            gameBoard->emitScore();
            pressed = false;}
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)){
            if(pressed){
            gameBoard->setLost(true);
            pressed = false;}
        }

}
void menuEventHandling(Menu* menu, bool pressed){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
    sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) > 50){
        if(pressed){
            menu->menuUp();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) < -50){
        if(pressed){
            menu->menuDown();
            }
       
        }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
        sf::Joystick::isButtonPressed(0,0)){
            if(pressed){
                menu->execute();
        }
    }

}
void Game::run(){
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    //gameBoard->instantiateGameBoard();

    using clock = std::chrono::high_resolution_clock;
    std::chrono::nanoseconds timePerFrame(1000000000 / FPS_SET);
    auto nextFrameTime = clock::now();
    unsigned int counter = 0;
    unsigned int secondsForNewLine = 5 * FPS_SET;
    sf::Clock gravityClock;
    sf::Clock newLineClock;

    while(window->isOpen()) {
        auto now = clock::now();
        bool pressed = true;
        while (const std::optional event = window->pollEvent()){
                    if (event->is<sf::Event::Closed>()){
                        window->close();
                    }     

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
                        window->close();
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
                        if(pressed){
                                gameBoard->instantiateGameBoard();
                            pressed =false;}
                        }
                    if(!gameBoard->isLost()){
                        activeGameEventHandling(gameBoard, pressed);
                        pressed = false;
                    }
                    else{
                        menuEventHandling(currentMenu, pressed);
                        pressed = false;
                    }
                }


        
        // Wenn noch Zeit bis zum nächsten Frame ist
                if (now < nextFrameTime) {
                    // Präzise warten
                    std::this_thread::sleep_until(nextFrameTime);
                }
                counter++;

                if(gameBoard->gravity(gravityClock.getElapsedTime().asSeconds())){
                    gravityClock.restart();
                }
                if(gameBoard->pushNewLine(newLineClock.getElapsedTime().asSeconds())){
                    newLineClock.restart();
                }
                window->clear(sf::Color::White);
                if(gameBoard->isLost()){
                            //gameBoard->drawLoseScreen(window);
                    currentMenu->draw(window);
                        }
                else{
                    gameBoard->draw(window);
                        }
                        
                window->display();
                
                nextFrameTime += timePerFrame;
    }
        }

void Game::setCurrentMenu(Menu* currentMenu){
    this->currentMenu = currentMenu;
}