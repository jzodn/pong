#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <format>

#include "Menu.hpp"
#include "Game.hpp"

int main() {
    Menu menu;
    menu.run_menu();

    Game game;
    game.run_game();

    return 0;
}