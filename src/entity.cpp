#include "entity.h"

Entity::Entity() {
}

Entity::Entity(sf::Texture& texture) {
    sprite.setTexture(texture);
}