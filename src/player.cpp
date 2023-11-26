#include "player.h"

#define MAX_VELOCITY 750.f
#define X_ACCELERATION 100.f
#define JUMP_ACCELERATION 2000.f

Player::Player()
{
}

Player::Player(sf::Texture& texture)
{
    sprite.setTexture(texture);
}

bool Player::onGround(sf::Time deltaTime)
{
    sf::Vector2f movingTo = velocity * deltaTime.asSeconds(); // where the sprite is attempting to move to

    if (sprite.getPosition().y + sprite.getLocalBounds().height + movingTo.y > 600) // bottom
    {
        return true;
    }
    else
        return false;
}

bool Player::checkBorderCollision(sf::Time deltaTime)
{
    sf::Vector2f movingTo = velocity * deltaTime.asSeconds(); // where the sprite is attempting to move to

    if ((sprite.getPosition().y) + movingTo.y < 0) // top
        velocity.y = 0; // IMPORTANT - need to move, works but really shouldn't be in a bool function

    if (sprite.getPosition().x + sprite.getLocalBounds().width + movingTo.x > 800 || sprite.getPosition().x + movingTo.x < 0) // left || right
        return true;
    else
        return false;
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

    velocity.y += JUMP_ACCELERATION/15; // gravity - change denominator to affect

    if (checkBorderCollision(deltaTime))
        velocity.x = 0;
    if (onGround(deltaTime)) {
        inAir = false;
        velocity.y = 0;
        velocity.x = velocity.x * 0.9f;
    }

    // max left & right velocity
    if (velocity.x > MAX_VELOCITY)
        velocity.x = MAX_VELOCITY;
    else if (velocity.x < -(MAX_VELOCITY))
        velocity.x = -(MAX_VELOCITY);

    sprite.move(velocity * deltaTime.asSeconds());
}