#include "tile.h"

Tile::Tile() {
}

Tile::Tile(sf::Texture& texture, int tile_size, int row, int col, int tileNum) {
    tileType = tileNum;

    // it just works lmao
    int x_start = (tileNum % 5)*tile_size; // gets x position of tile and multiplies by pixel amound
    int y_start = (tileNum / 5)*tile_size; // gets y position through integer division flooring

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(x_start, y_start, tile_size, tile_size)); 
	sprite.setPosition(col*tile_size, row*tile_size);
}