#pragma once

#include <SFML/Graphics.hpp>

// using tileMap = std::vector<std::vector<Tile>>;

class Player {
    public:
        Player();
        void update();
        void handleObjectCollision(sf::Time deltaTime, sf::Sprite object);
        // void handleBorderCollision(sf::Time deltaTime, sf::Vector2u windowSize);
        void move(sf::Time deltaTime);

        sf::Sprite sprite;
        sf::Vector2f velocity{0.0f, 0.0f};

        bool movingLeft = false, movingRight = false, jumping = false, inAir = false, crouching = false;
};