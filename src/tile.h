#pragma once

#include <SFML/Graphics.hpp>

class Tile {
	public:
		Tile();
		Tile(sf::Texture& texture, int tile_size, int pos_x, int pos_y, int tileNum);

		sf::Sprite sprite;

    private:
        int tileType;

};

/*
TILE TYPES:
0 - background
1 - default collidable
*/