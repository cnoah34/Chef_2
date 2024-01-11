#include "player.h"

#define MAX_X_VELOCITY 800.f
#define X_ACCELERATION 100.f
#define JUMP_ACCELERATION 2000.f
#define FRICTION 0.85f
#define GRAVITY 150.f

Player::Player() {
}

void Player::handleObjectCollision(sf::Time deltaTime, sf::Sprite object){
    sf::Vector2f movingTo = velocity * deltaTime.asSeconds(); 

    if(sprite.getGlobalBounds().intersects(object.getGlobalBounds())) {        
        // // left
        // if(sprite.getPosition().x + movingTo.x < object.getPosition().x + object.getLocalBounds().width) {
        //     velocity.x = 0;
        //     sprite.setPosition(object.getPosition().x + object.getLocalBounds().width, sprite.getPosition().y);
        // }

        // // right
        // if(sprite.getPosition().x + sprite.getLocalBounds().width + movingTo.x > object.getPosition().x) {
        //     velocity.x = 0;
        //     sprite.setPosition(object.getPosition().x - sprite.getLocalBounds().width, sprite.getPosition().y);
        // }

        // top
        // if(sprite.getPosition().y + movingTo.y < object.getPosition().y + object.getLocalBounds().height) {
        //     velocity.y = 0;
        //     sprite.setPosition(sprite.getPosition().x, object.getPosition().y + object.getLocalBounds().height);
        // }

        // bottom
        if(sprite.getPosition().y + sprite.getLocalBounds().height + movingTo.y >= object.getPosition().y) {
            inAir = false;
            velocity.y = 0.f;
            sprite.setPosition(sprite.getPosition().x, object.getPosition().y - sprite.getLocalBounds().height + 1); // +1 px
        }
    }
}

/*
void Player::handleBorderCollision(sf::Time deltaTime, sf::Vector2u windowSize) {
    sf::Vector2f movingTo = velocity * deltaTime.asSeconds(); 

    // left
    if(sprite.getPosition().x + movingTo.x < 0) {
        velocity.x = 0;
        sprite.setPosition(0, sprite.getPosition().y);
    }

    // right
    if(sprite.getPosition().x + sprite.getLocalBounds().width + movingTo.x > windowSize.x) {
        velocity.x = 0;
        sprite.setPosition(windowSize.x-sprite.getLocalBounds().width, sprite.getPosition().y);
    }

    // top
    if((sprite.getPosition().y) + movingTo.y < 0) {
        velocity.y = 0;
        sprite.setPosition(sprite.getPosition().x, 0);
    }

    // bottom
    if(sprite.getPosition().y + sprite.getLocalBounds().height + movingTo.y > windowSize.y) {
        inAir = false;
        velocity.y = 0;
        velocity.x *= FRICTION;
        sprite.setPosition(sprite.getPosition().x, windowSize.y-sprite.getLocalBounds().height);
    }
}
*/

void Player::move(sf::Time deltaTime) {
    sprite.move(velocity * deltaTime.asSeconds());
}

void Player::update() {
    // if(crouching)
    if(jumping && !inAir) {
        inAir = true;
        velocity.y -= JUMP_ACCELERATION;
    }
    if(movingLeft)
        velocity.x -= X_ACCELERATION;
    if(movingRight)
        velocity.x += X_ACCELERATION;

    velocity.y += GRAVITY; // gravity

    if(!inAir)
        velocity.x *= FRICTION;

    // max left & right velocity
    if(velocity.x > MAX_X_VELOCITY)
        velocity.x = MAX_X_VELOCITY;
    else if(velocity.x < -(MAX_X_VELOCITY))
        velocity.x = -(MAX_X_VELOCITY);
}
