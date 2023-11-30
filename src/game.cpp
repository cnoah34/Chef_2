#include "game.h"

#include <optional>
#include <string>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TILE_SIZE 80

// Chef 2: The Second Course

std::optional<sf::Texture> loadTexture(const std::string& filename) {
    sf::Texture tex;
    if (!tex.loadFromFile(filename))
    {
        return std::nullopt; // if the filename does not load, return a null optional
    }
    return tex; // otherwise, return the texture
}

Game::Game()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Chef: The Second Course", sf::Style::Close | sf::Style::Titlebar) {
    // errorTexOpt will either be the error texture or null
    std::optional<sf::Texture> errorTexOpt = loadTexture("../sprites/errorTexture188px.jpg");
    if (!errorTexOpt) 
    {
        window.close();
    }

    textureMap.emplace(std::make_pair("error", errorTexOpt.value())); // place the error texture into the map

    // load a texture, if the texture cannot load assign it the error texture
    textureMap.emplace(std::make_pair("playerTexture", loadTexture("../sprites/CowboyCropped.png").value_or(textureMap["error"])));
    textureMap.emplace(std::make_pair("bricks", loadTexture("../sprites/bricks.jpg").value_or(textureMap["error"])));

    // initialize texture and set the player's position to the middle of the screen
    Player newPlayer(textureMap.at("playerTexture"));
    newPlayer.sprite.setPosition(window.getSize().x / 2 - newPlayer.sprite.getLocalBounds().width / 2, window.getSize().y - newPlayer.sprite.getLocalBounds().height);

    player = newPlayer;

    for (int row = 0; row < window.getSize().y / TILE_SIZE; row++) {
        std::vector<Tile> rowVec;
        for (int col = 0; col < window.getSize().x / TILE_SIZE; col++) {
            int x_start = col * TILE_SIZE;
            int y_start = row * TILE_SIZE;
            rowVec.push_back(Tile(textureMap.at("bricks"), TILE_SIZE, x_start, y_start));
        }
        tileVec.push_back(rowVec);
    }
}

void Game::run() {
    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
    sf::Time timeSinceLastUpdate = sf::Time::Zero; // start "timer"

    while (window.isOpen()) {
        processEvents();

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }

        render();
    }
}

void Game::playerInput(sf::Keyboard::Key key, bool isPressed) {
    switch (key) {
        case sf::Keyboard::Escape:
            window.close();
            break;
        case sf::Keyboard::W:
            player.jumping = isPressed;
            break;
        case sf::Keyboard::S:
            player.crouching = isPressed;
            break;
        case sf::Keyboard::A:
            player.movingLeft = isPressed;
            break;
        case sf::Keyboard::D:
            player.movingRight = isPressed;
            break;
        default:
            break;
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::KeyPressed:
                playerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                playerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}

void Game::update(sf::Time deltaTime) {
    player.update(deltaTime, window.getSize());
}

void Game::render() {
    window.clear(); // must call clear before drawing anything
    for (int row = 0; row < tileVec.size(); row++) 
        for(int col = 0; col < tileVec[row].size(); col++) {
            window.draw(tileVec[row][col].sprite);
        }
    window.draw(player.sprite);
    window.display();
}