#include "entity.h"

Entity::Entity()
{
}

Entity::Entity(sf::Texture& texture)
{
    sprite.setTexture(texture);
    //sprite.setTextureRect(sf::IntRect(10, 10, 200, 400));
    sf::Vector2f scale = sprite.getScale();

    // NOT DONE
    sprite.setScale(scale.x * .1, scale.y * .1);

}