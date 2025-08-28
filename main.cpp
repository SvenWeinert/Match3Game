#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <chrono>
#include <thread>

class GameBoard;

const int FPS_SET = 60;

struct DestroyedTileCoordinate {
    unsigned int i;
    unsigned int j;
    
    DestroyedTileCoordinate(int i, int j) : i(i), j(j) {}
};

class ColorManager{
    private:
        sf::Color red = sf::Color::Red;
        sf::Color blue = sf::Color::Blue;
        sf::Color green = sf::Color::Green;
        sf::Color yellow = sf::Color::Yellow;
    public:
        ColorManager(){
            std::srand(std::time(0));
            red = sf::Color(255, 0, 97); 
            blue = sf::Color(0, 195, 255); 
            green = sf::Color(17, 230, 45); 
            yellow = sf::Color(255, 188, 45); 
        }

        sf::Color getRandomColor(){
            int randomInt = std::rand() % 4;

            switch(randomInt){
                case 0: return red;
                case 1: return blue;
                case 2: return green;
                case 3: return yellow;
                default: return red;
        }
        return blue;
    }



};



class Tile{
    private:
        bool active = false;
        sf::RectangleShape rectangle;

    public:
        Tile() : active(false), rectangle(sf::Vector2f(64.f, 64.f)){}
        void draw(sf::RenderWindow* window){
            window->draw(rectangle);
        }
        void setActive(bool active){this->active = active;}
        bool isActive(){ return this->active;}

        void setFillColor(const sf::Color& color) {
        rectangle.setFillColor(color);
        }
        sf::Color getFillColor(){
            return rectangle.getFillColor();
        }

        void updatePosition(const unsigned int i, const unsigned int j){
            rectangle.setPosition(sf::Vector2f((768 + (j * 64)), (1080 - 140 - (i*64))));
        }


};

class GameBoard{
    private:
        std::vector<std::vector<Tile>> gameBoard;
        unsigned int xCrdCursor = 0;
        unsigned int yCrdCursor = 0;
        ColorManager cM;
        sf::Sprite cursor;
        bool gameLost = false;
        unsigned int gameScore = 0;
        sf::Text scoreText;
        
    
    public:
        GameBoard(sf::Sprite cursor, sf::Text scoreText) : gameBoard(12, std::vector<Tile>(6)), cM(), cursor(cursor), scoreText(scoreText){
           
        }
        
        void draw(sf::RenderWindow* window){
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

        void drawLoseScreen(sf::RenderWindow* window){

            scoreText.setPosition(sf::Vector2f(410.f, 200.f));
            scoreText.setString("GAME OVER SCORE: " + std::to_string(gameScore));
            window->draw(scoreText);

        }
        void instantiateGameBoard(){
            scoreText.setPosition(sf::Vector2f(767.f, 155.f));
            scoreText.setFillColor(sf::Color::Black);
            scoreText.setCharacterSize(80);
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
        cursor.setPosition(sf::Vector2f((768 + (xCrdCursor * 64)), (940 - (yCrdCursor*64))));
        }
        void upKey(){
            if(yCrdCursor != 11){
                yCrdCursor++;
                updateCursor();
            }
        }
        void downKey(){
            if(yCrdCursor != 0){
                yCrdCursor--;
                updateCursor();
        }}
        void leftKey(){
            if(xCrdCursor != 0){
                xCrdCursor--;
                updateCursor();
            }}
        void rightKey(){
            if(xCrdCursor != 4){
                xCrdCursor++;
                updateCursor();
            }
        }
        void updateCursor(){
            cursor.setPosition(sf::Vector2f((768 + (xCrdCursor * 64)), (1080 - 140 - (yCrdCursor*64))));
            
        }

        void switchTiles(){
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

        void emitScore() {
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
        
    void gravity(){
        for(unsigned int i = 1; i < gameBoard.size(); i++) {
                for(unsigned int j = 0; j < gameBoard[0].size(); j++) {
                    if(!gameBoard[i -1][j].isActive() && gameBoard[i][j].isActive()){
                gameBoard[i][j].setActive(false);
                gameBoard[i-1][j].setActive(true);
                gameBoard[i-1][j].setFillColor(gameBoard[i][j].getFillColor());
                    }
                }
            }
        }
    
    void pushNewLine(){
        if(checkIfTerminal()){
            gameLost=true;
        }
        else{
            for(int i = 0; i < gameBoard[11].size(); i++){
                gameBoard[11][i].setFillColor(cM.getRandomColor());
                gameBoard[11][i].setActive(true);
            }
        }
    }
    bool checkIfTerminal(){
        for(unsigned int i = 0; i < gameBoard[11].size(); i++){
            if(gameBoard[11][i].isActive()){
                return true;
            }
        }
        return false;
    }

    bool isLost(){ return this->gameLost;}

};
class Game{
    public:
        sf::RenderWindow * window;
        GameBoard * gameBoard;
        void run(){
            sf::CircleShape shape(100.f);
            shape.setFillColor(sf::Color::Green);
            gameBoard->instantiateGameBoard();

            using clock = std::chrono::high_resolution_clock;
            std::chrono::nanoseconds timePerFrame(1000000000 / FPS_SET);
            auto nextFrameTime = clock::now();
            unsigned int counter = 0;
            unsigned int secondsForNewLine = 5 * FPS_SET;
    
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
                            if(!gameBoard->isLost()){
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
                                    if(pressed){
                                    gameBoard->upKey();
                                    pressed = false;}
                                }
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
                                    if(pressed){
                                    gameBoard->leftKey();
                                    pressed = false;}
                                }
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
                                    if(pressed){
                                    gameBoard->downKey();
                                    pressed = false;}
                                }
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
                                    if(pressed){
                                    gameBoard->rightKey();
                                    pressed = false;}
                                }
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
                                    if(pressed){
                                    gameBoard->switchTiles();
                                    pressed = false;}
                                }
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)){
                                    if(pressed){
                                    gameBoard->emitScore();
                                    pressed = false;}
                                }
                                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
                                    if(pressed){
                                    gameBoard->gravity();
                                    pressed = false;}
                                }
                            }
                        }
                
                // Wenn noch Zeit bis zum nächsten Frame ist
                        if (now < nextFrameTime) {
                            // Präzise warten
                            std::this_thread::sleep_until(nextFrameTime);
                        }
                        counter++;
                        if(counter% FPS_SET == 0){
                            gameBoard->gravity();
                        }
                        if(counter % secondsForNewLine == 0){
                            gameBoard->pushNewLine();
                            counter = 0;
                        }
                        // Update und Rendering
                                window->clear(sf::Color::White);
                                if(gameBoard->isLost()){
                                    gameBoard->drawLoseScreen(window);
                                }
                                else{
                                    gameBoard->draw(window);
                                }
                                
                                window->display();
                        
                        nextFrameTime += timePerFrame;
            }
                }

};

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({1920, 1080}), "SFML works!", sf::Style::None, sf::State::Fullscreen);
    sf::Texture texture("image.png", false, sf::IntRect({0, 0}, {128, 64}));
    sf::Sprite cursor(texture);

    sf::Font arial("arial.ttf");
    sf::Text scoreText(arial);
    

    GameBoard* gameBoard = new GameBoard(cursor, scoreText);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    Game game;
    game.gameBoard = gameBoard;
    game.window = window;

    game.run();


}