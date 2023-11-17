#include "player.h"

Player::Player(){}

void Player::initTexture(sf::Texture texture)
{
    playerTexture = texture; // playerTexture variable must exist so that the texture is not destroyed
    playerSprite.setTexture(playerTexture);
}