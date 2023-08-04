#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <string>

class Game
{
    public:
        Game();
        void run();

    private:
        sf::RenderWindow window;
        sf::Sprite player;
        sf::Sprite bricks;

        sf::RectangleShape rect;

        std::unordered_map<std::string, sf::Texture> textureMap; // a map to contain all of the entity textures

        bool crouch = false, movingLeft = false, movingRight = false, inAir = false;

        int jumpFrames = 0;

        void playerInput(sf::Keyboard::Key key, bool isPressed);

        void processEvents();
        sf::Vector2f checkBorderCollision(sf::Vector2f movement, sf::Time deltaTime);
        void update(sf::Time deltaTime);
        void render();
};

#endif