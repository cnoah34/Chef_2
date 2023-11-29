#include "tile.h"

Tile::Tile() {
}

Tile::Tile(sf::Texture& texture, int tile_size, int x_start, int y_start) {
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(x_start, y_start, tile_size, tile_size));
	sprite.setPosition(x_start, y_start);
}