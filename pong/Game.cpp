#include "Game.hpp"

Paddle::Paddle(float x, int index) {
    paddle.setSize(sf::Vector2f(20.f, 124.f));
    paddle.setOrigin(10.f, 62.f);
    paddle.setPosition(x, 300.f);

    this->index = index;
    score = 0;

    boundingBox = paddle.getGlobalBounds();
}

void Paddle::moveUp() {
    if (paddle.getPosition().y > 62.f) {
        paddle.move(0.f, -10.f);
    }

    boundingBox = paddle.getGlobalBounds();
}

void Paddle::moveDown() {
    if (paddle.getPosition().y < 538.f) {
        paddle.move(0.f, 10.f);
    }

    boundingBox = paddle.getGlobalBounds();
}

Ball::Ball() {
    ball.setSize(sf::Vector2f(16.f, 16.f));
    ball.setOrigin(8.f, 8.f);
    ball.setPosition(500.f, 300.f);

    boundingBox = ball.getGlobalBounds();

    velocity = 5.;
    angle = 0;
}

void Ball::move(std::vector<Paddle*> paddles) {
    for (auto paddle : paddles) {
        if (boundingBox.intersects(paddle->boundingBox)) {
            handlePaddleCollision(*paddle);
        }
    }

    if (ball.getPosition().y > 600 || ball.getPosition().y < 0) {
        angle = -angle;
    }
    else if (ball.getPosition().x > 1000) {
        paddles[0]->score++;
        resetBall(1);
    }
    else if (ball.getPosition().x < 0) {
        paddles[1]->score++;
        resetBall(0);
    }

    ball.move(cos(angle) * velocity, tan(angle) * velocity);

    boundingBox = ball.getGlobalBounds();
}

void Ball::handlePaddleCollision(Paddle paddle) {
    float relativeIntersectY = (paddle.paddle.getPosition().y - ball.getPosition().y) / paddle.paddle.getSize().y;
    angle = relativeIntersectY * (-PI / 2) + (paddle.index == 1 ? PI : 0);
}

void Ball::resetBall(int direction) {
    ball.setPosition(500.f, 300.f);
    angle = PI * direction;
}

Game::Game() {
    window = new sf::RenderWindow();
    font = new sf::Font();

    set_values();
}

Game::~Game() {
    delete window;
    delete font;
    delete ball;

    for (auto paddle : paddles) {
        delete paddle;
    }
}

void Game::set_values() {
    window->create(sf::VideoMode(1000, 600), "Pong - Game");
    window->setFramerateLimit(144);

    if (!font->loadFromFile("./arial.ttf")) {
        printf("error");
    }

    paddles.resize(2);
    paddles[0] = new Paddle(50.f, 0);
    paddles[1] = new Paddle(950.f, 1);

    coords = { {450.f, 50.f}, {550.f,50.f} };

    scores.resize(2);
    for (std::size_t i{}; i < scores.size(); ++i) {
        scores[i].setFont(*font);
        scores[i].setString("0");
        scores[i].setFillColor(sf::Color::White);
        scores[i].setCharacterSize(50);
        scores[i].setPosition(coords[i]);
    }

    ball = new Ball();
}

void Game::loop_events() {
    sf::Event event;

    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            paddles[0]->moveUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            paddles[0]->moveDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            paddles[1]->moveUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            paddles[1]->moveDown();
        }
    }
}

void Game::update() {
    scores[0].setString(std::to_string(paddles[0]->score));
    scores[1].setString(std::to_string(paddles[1]->score));

    ball->move(paddles);
}

void Game::render() {
    window->clear();

    for (auto score : scores) {
        window->draw(score);
    }

    for (auto paddle : paddles) {
        window->draw(paddle->paddle);
    }

    window->draw(ball->ball);

    window->display();
}

void Game::run_game() {
    while (window->isOpen()) {
        loop_events();
        update();
        render();
    }
}