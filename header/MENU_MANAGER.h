#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

// Forward Declaration
class Menu;

class MenuManager {
private:
    Menu* startMenu;
    Menu* scoreMenu;
    
public:
    Menu* getStartMenu();
    Menu* getScoreMenu();
    
    void setStartMenu(Menu* startMenu);
    void setScoreMenu(Menu* scoreMenu);
};

#endif