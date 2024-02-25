#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <format>

#include "Menu.hpp"
#include "Game.hpp"

int main() {
    Menu* menu = new Menu;
    menu->run_menu();
    
    if (menu->get_pos() == 1) {
        delete menu;

        Game game;
        game.run_game();
    }
    else {
        delete menu;
    }

    return 0;
}