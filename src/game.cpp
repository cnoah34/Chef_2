#include <optional>
#include <iostream>

#include "game.h"

#define HOR 800
#define VER 600

// Chef 2: The Final Course
// Chef 2: The Second Course

#define STRINGIFY(X) (#X)

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
    auto errorTexOpt = loadTexture("../sprites/errorTexture.jpg");
    if (!errorTexOpt)
    {
        window.close();
    }

    textureMap.emplace(std::make_pair("error", errorTexOpt.value())); // place the error texture into the map

    // load the player texture and if the texture cannot load, assign it the error texture
    sf::Texture playerTexture = loadTexture("../sprites/Cowboy150pxCropped.png").value_or(textureMap["error"]);
    textureMap.emplace(std::make_pair("playerTexture", playerTexture));

    player.initTexture(textureMap.at("playerTexture"));

    // start the player in the middle of the screen
    player.playerSprite.setPosition(HOR / 2 - player.playerSprite.getLocalBounds().width / 2, VER - player.playerSprite.getLocalBounds().height);
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
    {
        if (isPressed && !inAir)
        {
            jumpFrames = 10;
        }
    }
    if (key == sf::Keyboard::S)
        crouch = isPressed;
    if (key == sf::Keyboard::A)
        movingLeft = isPressed;
    if (key == sf::Keyboard::D)
        movingRight = isPressed;
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

// enum class Collision
// {
//     NoCollide,
//     Side,
//     Top,
//     Bottom,
// };

/*
Collision rectIntersect(sf::Sprite& player, sf::RectangleShape& rectangle)
{
      sf::Vector2f playerPos = player.getPosition();
      sf::FloatRect playerBounds = player.getLocalBounds();

     sf::Vector2f rectPos = rectangle.getPosition();
     sf::FloatRect rectBounds = rectangle.getLocalBounds();
 }
 */

sf::Vector2f Game::checkBorderCollision(sf::Vector2f movement, sf::Time deltaTime)
{
    sf::Vector2f playerPos = player.playerSprite.getPosition();
    sf::FloatRect playerBounds = player.playerSprite.getLocalBounds();

    sf::Vector2f movingTo = movement * deltaTime.asSeconds();

    // check to see if one side of the sprite is attempting to move out of bounds and if so set movement in that direction to 0
    if ((playerPos.y + playerBounds.height) + movingTo.y > VER) // bottom
    {
        player.playerSprite.setPosition(playerPos.x, VER - playerBounds.height);
        inAir = false;
        movement.y = 0;
    }
    if ((playerPos.y) + movingTo.y < 0) // top
        movement.y = 0;
    if ((playerPos.x + playerBounds.width) + movingTo.x > HOR) // right
        movement.x = 0;
    if ((playerPos.x) + movingTo.x < 0) // left
        movement.x = 0;

    /*
    // testing collisions with rectangles
    sf::Vector2f rectPos = rect.getPosition(); // get the current position of the sprite
    sf::FloatRect rectBounds = rect.getLocalBounds(); // gets the bounds of the sprite

    // entity collisions
    // falling
    if(playerPos.x >= rectPos.x && playerPos.x <= (rectPos.x + rectBounds.width)
        && (playerPos.y < rectPos.y)
        && ((playerPos.y + playerBounds.height) + movingTo.y) > rectPos.y)
        {
            player.setPosition(playerPos.x, rectPos.y - playerBounds.height);
            inAir = false;
            movement.y = 0;
        }
    // jumping up into
    if(playerPos.x + playerBounds.width >= rectPos.x
        && playerPos.x <= (rectPos.x + rectBounds.width)
        && (playerPos.y > rectPos.y)
        && ((playerPos.y) + movingTo.y) < rectPos.y + rectBounds.height)
        {
            player.setPosition(playerPos.x, (rectPos.y + rectBounds.height));
            movement.y = 0;
        }
    */
    

    return movement;
}

void Game::update(sf::Time deltaTime) // 530.3f x & y for uniform diagonal
{
    sf::Vector2f movement(0.f, 0.f); // initialize movement for the frame

    float jumpVelocity = 2000.f;

    if (jumpFrames > 0)
    {
        movement.y -= jumpVelocity;
        inAir = true;
        jumpFrames--;
    }
    //if(crouch)
    if (movingLeft)
        movement.x -= 750.f;
    if (movingRight)
        movement.x += 750.f;

    movement.y += jumpVelocity / 2.0f; // gravity

    movement = checkBorderCollision(movement, deltaTime);
    player.playerSprite.move(movement * deltaTime.asSeconds());
}

void Game::render()
{
    // const sf::Color &color = Color(0, 0, 0, 255);
    window.clear(); // must call clear before drawing anything
    window.draw(player.playerSprite);
    //window.draw(rect); // create an array of entities and loop to draw?
    window.display();
}