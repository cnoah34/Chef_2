#pragma once

#include <SFML/Graphics.hpp>

class Entity {
    public:
        Entity();
        Entity(sf::Texture& texture);

        sf::Sprite sprite;
};