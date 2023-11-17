#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{

    public:
        Player(sf::Texture initTexture);

    private:
        sf::Texture texture;
};

#endif