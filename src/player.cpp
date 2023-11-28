#include "player.h"

// need to figure out how to put HOR & VER in one place, currently in game.cpp and player.cpp
#define HOR 800
#define VER 600
#define MAX_VELOCITY 750.f
#define X_ACCELERATION 100.f
#define JUMP_ACCELERATION 2000.f
#define FRICTION 0.85f
#define GRAVITY 150.f

Player::Player()
{
}

Player::Player(sf::Texture& texture)
{
    sprite.setTexture(texture);
}

void Player::handleBorderCollision(sf::Time deltaTime)
{
    sf::Vector2f movingTo = velocity * deltaTime.asSeconds(); 

    // left
    if (sprite.getPosition().x + movingTo.x < 0) {
        velocity.x = 0;
        sprite.setPosition(0, sprite.getPosition().y);
    }

    // right
    if (sprite.getPosition().x + sprite.getLocalBounds().width + movingTo.x > HOR) {
        velocity.x = 0;
        sprite.setPosition(HOR-sprite.getLocalBounds().width, sprite.getPosition().y);
    }

    // top
    if ((sprite.getPosition().y) + movingTo.y < 0) {
        velocity.y = 0;
        sprite.setPosition(sprite.getPosition().x, 0);
    }

    // bottom
    if (sprite.getPosition().y + sprite.getLocalBounds().height + movingTo.y > VER) {
        inAir = false;
        velocity.y = 0;
        velocity.x = velocity.x * FRICTION;
        sprite.setPosition(sprite.getPosition().x, VER-sprite.getLocalBounds().height);
    }
}


void Player::update(sf::Time deltaTime)
{
    //if(crouching)
    if (jumping && !inAir) {
        inAir = true;
        velocity.y -= JUMP_ACCELERATION;
    }
    if (movingLeft)
        velocity.x -= X_ACCELERATION;
    if (movingRight)
        velocity.x += X_ACCELERATION;

    velocity.y += GRAVITY; // gravity

    // max left & right velocity
    if (velocity.x > MAX_VELOCITY)
        velocity.x = MAX_VELOCITY;
    else if (velocity.x < -(MAX_VELOCITY))
        velocity.x = -(MAX_VELOCITY);

    handleBorderCollision(deltaTime);

    sprite.move(velocity * deltaTime.asSeconds());
}