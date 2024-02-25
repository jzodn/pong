#pragma once

#include <SFML/Graphics.hpp>

class Menu {
	sf::RenderWindow* window;
	sf::Font* font;

	int pos;
	bool pressed, theselect;
	
	sf::Vector2i pos_mouse;
	sf::Vector2f mouse_coord;

	std::vector<const char*> options;
	std::vector<sf::Vector2f> coords;
	std::vector<sf::Text> texts;
	std::vector<std::size_t> sizes;

	void set_values();
	void loop_events();
	void render();

public:
	Menu();
	int get_pos();
	~Menu();
	void run_menu();

};