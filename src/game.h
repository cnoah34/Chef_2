#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "player.h"
#include "tile.h"
#include "entity.h"

class Game {
    public:
        Game();
        void run();

    private:
        sf::RenderWindow window;
        Player player;
        std::vector<std::vector<Tile>> tileVec;
        std::unordered_map<std::string, sf::Texture> textureMap; // a map to contain all textures

        void playerInput(sf::Keyboard::Key key, bool isPressed);

        void processEvents();
        void update(sf::Time deltaTime);
        void render();
};