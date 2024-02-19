#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <format>

#define PI 3.14159

struct Paddle {
    sf::RectangleShape paddle;
    sf::FloatRect boundingBox;
    int index;
    int score;

    Paddle(float x, int index) {
        paddle.setSize(sf::Vector2f(20.f, 124.f));
        paddle.setOrigin(10.f, 62.f);
        paddle.setPosition(x, 300.f);

        this->index = index;
        score = 0;

        boundingBox = paddle.getGlobalBounds();
    }

    void moveUp() {
        if (paddle.getPosition().y > 62.f) {
            paddle.move(0.f, -5.f);
        }

        boundingBox = paddle.getGlobalBounds();
    }

    void moveDown() {
        if (paddle.getPosition().y < 538.f) {
            paddle.move(0.f, 5.f);
        }

        boundingBox = paddle.getGlobalBounds();
    }
};

class Ball {
public:
    sf::RectangleShape ball;
    sf::FloatRect boundingBox;

private:
    float velocity;
    float angle;

public:
    Ball() {
        ball.setSize(sf::Vector2f(16.f, 16.f));
        ball.setOrigin(8.f, 8.f);
        ball.setPosition(500.f, 300.f);

        boundingBox = ball.getGlobalBounds();

        velocity = 3.;
        angle = 0;
    }

    void move(Paddle& paddle0, Paddle& paddle1) {
        if (boundingBox.intersects(paddle0.boundingBox)) {
            handlePaddleCollision(paddle0);
        }
        else if (boundingBox.intersects(paddle1.boundingBox)) {
            handlePaddleCollision(paddle1);
        }
        else if (ball.getPosition().y > 600 || ball.getPosition().y < 0) {
            angle = -angle;
        }
        else if (ball.getPosition().x > 1000) {
            paddle0.score++;
            resetBall(1);
        }
        else if (ball.getPosition().x < 0) {
            paddle1.score++;
            resetBall(0);
        }

        ball.move(cos(angle) * velocity, tan(angle) * velocity);

        boundingBox = ball.getGlobalBounds();
    }

private:
    void handlePaddleCollision(Paddle paddle) {
        float relativeIntersectY = (paddle.paddle.getPosition().y - ball.getPosition().y) / paddle.paddle.getSize().y;
        angle = relativeIntersectY * (-PI / 2) + (paddle.index == 1 ? PI : 0);
    }

    void resetBall(int direction) {
        ball.setPosition(500.f, 300.f);
        angle = PI * direction;
    }
};


int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Pong!");

    sf::Font font;
    if (!font.loadFromFile("./arial.ttf")) {
        printf("ERROR");
    }

    sf::Text score0;
    sf::Text score1;

    score0.setCharacterSize(30);
    score0.setFillColor(sf::Color::White);
    score0.setFont(font);
    score0.setPosition(50.f, 50.f);
    score0.setStyle(sf::Text::Bold);

    score1.setCharacterSize(30);
    score1.setFillColor(sf::Color::White);
    score1.setFont(font);
    score1.setPosition(800.f, 50.f);
    score1.setStyle(sf::Text::Bold);

    Paddle paddle0(50.f, 0);
    Paddle paddle1(950.f, 1);

    Ball ball;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            paddle0.moveUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            paddle0.moveDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            paddle1.moveUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            paddle1.moveDown();
        }

        ball.move(paddle0, paddle1);

        score0.setString("Player 1: " + std::to_string(paddle0.score));
        score1.setString("Player 2: " + std::to_string(paddle1.score));

        window.clear();
        window.draw(paddle0.paddle);
        window.draw(paddle1.paddle);
        window.draw(ball.ball);
        window.draw(score0);
        window.draw(score1);
        window.display();
    }

    return 0;
}