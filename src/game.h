#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.h"

#include <unordered_map>
#include <string>

class Game
{
    public:
        Game();
        void run();

    private:
        sf::RenderWindow window;

        Player player;

        std::unordered_map<std::string, sf::Texture> textureMap; // a map to contain all of the entity textures

        void playerInput(sf::Keyboard::Key key, bool isPressed);

        void processEvents();
        void update(sf::Time deltaTime);
        void render();
};

#endif