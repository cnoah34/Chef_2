#include <optional>
#include <iostream>

#include "game.h"

#define HOR 800
#define VER 600

// Chef 2: The Second Course

std::optional<sf::Texture> loadTexture(const std::string& filename)
{
    sf::Texture tex;
    if (!tex.loadFromFile(filename))
    {
        return std::nullopt; // if the filename does not load, return a null optional
    }
    return tex; // otherwise, return the texture
}

Game::Game()
    : window(sf::VideoMode(HOR, VER), "Chef: The Second Course", sf::Style::Close | sf::Style::Titlebar)
{
    std::optional<sf::Texture> errorTexOpt = loadTexture("../sprites/errorTexture188px.jpg");
    if (!errorTexOpt)
    {
        window.close();
    }

    textureMap.emplace(std::make_pair("error", errorTexOpt.value())); // place the error texture into the map

    // load the player texture and if the texture cannot load, assign it the error texture
    sf::Texture playerTexture = loadTexture("../sprites/CowboyCropped.png").value_or(textureMap["error"]);
    textureMap.emplace(std::make_pair("playerTexture", playerTexture));

    // initialize texture and set the player's position to the middle of the screen
    Player newPlayer(textureMap.at("playerTexture"));
    newPlayer.sprite.setPosition(HOR / 2 - newPlayer.sprite.getLocalBounds().width / 2, VER - newPlayer.sprite.getLocalBounds().height);

    player = newPlayer;
}

void Game::run()
{
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

void Game::playerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
        player.jumping = isPressed;
    if (key == sf::Keyboard::S)
        player.crouching = isPressed;
    if (key == sf::Keyboard::A)
        player.movingLeft = isPressed;
    if (key == sf::Keyboard::D)
        player.movingRight = isPressed;
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
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

void Game::update(sf::Time deltaTime) // 530.3f x & y for uniform diagonal
{
    sf::Vector2f movement(0.f, 0.f);

    player.update(deltaTime);
}

void Game::render()
{
    window.clear(); // must call clear before drawing anything
    window.draw(player.sprite);
    window.display();
}