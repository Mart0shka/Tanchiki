#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Tank.hpp"
#include "ConvertSketch.hpp"

#pragma once

std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const std::array<std::string, MAP_HEIGHT>& map_sketch, Tank& i_tank) {
	//эта шн€га отрисовывает нам карту в зависимости от символа;

	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> output_map;

	for (unsigned char i = 0; i < MAP_HEIGHT; ++i) {
		for (unsigned char j = 0; j < MAP_WIDTH; ++j) {
			output_map[j][i] = Cell::Empty;

			switch (map_sketch[i][j]) {
				case '#':
				{
					output_map[j][i] = Cell::Wall;
					break;
				}
				case 'T':
				{
					i_tank.set_position(CELL_SIZE * j, CELL_SIZE * i);
					break;
				}
			}
			

		}
	}

	return output_map;


}
