#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"
#include "tile.h"
#include "entity.h"

#include <unordered_map>
#include <string>

class Game {
    public:
        Game();
        void run();

    private:
        sf::RenderWindow window;

        Player player;

        // vector of vectors containing tiles
        std::vector<std::vector<Tile>> tileVec;

        std::unordered_map<std::string, sf::Texture> textureMap; // a map to contain all of the entity textures

        void playerInput(sf::Keyboard::Key key, bool isPressed);

        void processEvents();
        void update(sf::Time deltaTime);
        void render();
};