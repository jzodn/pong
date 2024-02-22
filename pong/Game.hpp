#pragma once

#include <SFML/Graphics.hpp>

#define PI 3.14159

struct Paddle {
    sf::RectangleShape paddle;
    sf::FloatRect boundingBox;
    int index;
    int score;

    Paddle(float x, int index);

    void moveUp();

	void moveDown();
};

class Ball {
public:
    sf::RectangleShape ball;
    sf::FloatRect boundingBox;

private:
    float velocity;
    float angle;

public:
    Ball();
    void move(std::vector<Paddle*>);

private:
	void handlePaddleCollision(Paddle paddle);
	void resetBall(int direction);
};

class Game {
	sf::RenderWindow* window;
	sf::Font* font;

	std::vector<Paddle*> paddles;

	std::vector<sf::Text> scores;
	std::vector<std::size_t> sizes;
	std::vector<sf::Vector2f> coords;

	Ball* ball;

	void set_values();
	void loop_events();
	void update();
	void render();

public:
	Game();
	~Game();
	void run_game();

};