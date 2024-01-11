#include "game.h"

#include <optional>
#include <string>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TILE_SIZE 80

// Chef 2: The Second Course

std::optional<sf::Texture> loadTexture(const std::string& filename) {
    sf::Texture tex;
    if(!tex.loadFromFile(filename))
        return std::nullopt; // if the filename does not load, return a null optional
    else
        return tex; // otherwise, return the texture (being explicit here, else not technically needed)
}

Game::Game()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Chef: The Second Course", sf::Style::Close | sf::Style::Titlebar) {
    // errorTexOpt will either be the error texture or null
    std::optional<sf::Texture> errorTexOpt = loadTexture("../sprites/errorTexture188px.jpg");
    if(!errorTexOpt)
        window.close();

    textureMap.emplace(std::make_pair("error", errorTexOpt.value())); // place the error texture into the map

    // load a texture, if the texture cannot load assign it the error texture
    textureMap.emplace(std::make_pair("playerTexture", loadTexture("../sprites/CowboyCropped.png").value_or(textureMap["error"])));
    textureMap.emplace(std::make_pair("tileMap", loadTexture("../sprites/tileMap.png").value_or(textureMap["error"])));

    // initialize texture and set the player's position to the middle of the screen
    player.sprite.setTexture(textureMap.at("playerTexture"));
    player.sprite.setPosition(window.getSize().x / 2 - player.sprite.getLocalBounds().width / 2, window.getSize().y - player.sprite.getLocalBounds().height + TILE_SIZE);

    int tiles[9][16] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    for(int row = 0; row < (sizeof(tiles)/sizeof(tiles[0])); row++) {
        std::vector<Tile> rowVec;
        for(int col = 0; col < (sizeof(tiles[0])/sizeof(int)); col++) {
            // texture, size of a tile, col pos, row pos, tile type
            rowVec.push_back(Tile(textureMap.at("tileMap"), TILE_SIZE, row, col, tiles[row][col]));
        }
        tileVec.push_back(rowVec);
    }
}

void Game::run() {
    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
    sf::Time timeSinceLastUpdate = sf::Time::Zero; // start timer

    while(window.isOpen()) {
        processEvents();

        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }
        render();
    }
}

void Game::playerInput(sf::Keyboard::Key key, bool isPressed) {
    switch(key) {
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
    while(window.pollEvent(event)) {
        switch(event.type) {
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
    player.update();

    for(int row = 0; row < tileVec.size(); row++) {
        for(int col = 0; col < tileVec[row].size(); col++) {
            if(tileVec[row][col].tileType == 1) {
                player.handleObjectCollision(deltaTime, tileVec[row][col].sprite);
            }
        }
    }

    player.move(deltaTime);
}

void Game::render() {
    window.clear(); // must call clear before drawing anything
    for(int row = 0; row < tileVec.size(); row++) {
        for(int col = 0; col < tileVec[row].size(); col++) {
            window.draw(tileVec[row][col].sprite);
        }
    }
    window.draw(player.sprite);
    window.display();
}