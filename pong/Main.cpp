#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

struct Paddle {
    sf::RectangleShape paddle;
    sf::FloatRect boundingBox;

    Paddle(float x) {
        paddle.setSize(sf::Vector2f(20.f, 124.f));
        paddle.setOrigin(10.f, 62.f);
        paddle.setPosition(x, 300.f);

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

    void move(Paddle paddle0, Paddle paddle1) {
        if (boundingBox.intersects(paddle0.boundingBox)) {
            angle = (paddle0.paddle.getPosition().y - ball.getPosition().y) / 124;
            angle = angle * 90;

            velocity = -velocity;
        } else if (boundingBox.intersects(paddle1.boundingBox)) {
            angle = (paddle1.paddle.getPosition().y - ball.getPosition().y) / 124;
            angle = angle * 90;

            printf("%f\n", angle);

            velocity = -velocity;
        }

        ball.move(cos(angle)*velocity, tan(angle)*velocity);

        boundingBox = ball.getGlobalBounds();
    }
};
    

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Pong!");

    Paddle paddle0(50.f);
    Paddle paddle1(950.f);

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

        window.clear();
        window.draw(paddle0.paddle);
        window.draw(paddle1.paddle);
        window.draw(ball.ball);
        window.display();
    }

    return 0;
}