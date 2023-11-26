#pragma once

#include <SFML/Graphics.hpp>

class Player
{

    public:
        Player();
        Player(sf::Texture& texture);
        void update(sf::Time deltaTime);
        void handleBorderCollision(sf::Time deltaTime);

        sf::Sprite sprite;
        sf::Vector2f velocity{ 0.0f, 0.0f };

        bool movingLeft = false, movingRight = false, jumping = false, inAir = false, crouching = false;

        // should move some public members to private when the class is closer to being finished
    private:
};