#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{

    public:
        Player();
        void initTexture(sf::Texture texture);

        sf::Texture playerTexture;
        sf::Sprite playerSprite;

    private:
};

#endif