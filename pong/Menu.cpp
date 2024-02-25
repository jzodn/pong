#include "Menu.hpp"
#include "Game.hpp"

Menu::Menu() {
	window = new sf::RenderWindow();
	font = new sf::Font();

	set_values();
}

Menu::~Menu() {
	delete window;
	delete font;
}

void Menu::set_values() {
	window->create(sf::VideoMode(1000, 600), "Pong - Main Menu", sf::Style::Titlebar | sf::Style::Close);

	font->loadFromFile("./arial.ttf");

	pos = 1;
	pressed = theselect = false;

	pos_mouse = { 0, 0 };
	mouse_coord = { 0, 0 };

	options = { "Pong!", "Play", "Quit" };
	texts.resize(3);
	coords = { {450, 100}, {450, 200}, {450, 300} };
	sizes = { 30, 25, 25 };
	
	for (std::size_t i{}; i < texts.size(); ++i) {
		texts[i].setFont(*font);
		texts[i].setString(options[i]);
		texts[i].setCharacterSize(sizes[i]);
		texts[i].setFillColor(sf::Color::White);
		texts[i].setOutlineColor(sf::Color::Blue);
		texts[i].setPosition(coords[i]);
	}

	texts[pos].setOutlineThickness(4);
}

void Menu::loop_events() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		}

		pos_mouse = sf::Mouse::getPosition(*window);
		mouse_coord = window->mapPixelToCoords(pos_mouse);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
			if (pos < 2) {
				pos++;
				pressed = true;
				texts[pos].setOutlineThickness(4);
				texts[pos - 1].setOutlineThickness(0);
				pressed = false;
				theselect = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
			if (pos >  1) {
				pos--;
				pressed = true;
				texts[pos].setOutlineThickness(4);
				texts[pos + 1].setOutlineThickness(0);
				pressed = false;
				theselect = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
			theselect = true;
			if (pos == 1) {
				window->close();
			}
			if (pos == 2) {
				window->close();
			}
		}
	}
}

void Menu::render() {
	window->clear();
	
	for (auto t : texts) {
		window->draw(t);
	}
	
	window->display();
}

void Menu::run_menu() {
	while (window->isOpen()) {
		loop_events();
		render();
	}
}

int Menu::get_pos() {
	return pos;
}