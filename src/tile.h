#pragma once

#include <SFML/Graphics.hpp>

class Tile {
	public:
		Tile();
		Tile(sf::Texture& texture, int tile_size, int x_start, int y_start);
		sf::Sprite sprite;
};