#include <array>
#include <cmath>

#include "Global.hpp"
#include "MapCollision.hpp"

bool map_collision(short i_x, short i_y, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
	bool output = 0;

	//Getting the exact position.
	float cell_x = i_x / static_cast<float>(CELL_SIZE);
	float cell_y = i_y / static_cast<float>(CELL_SIZE);

	//A Tank can intersect 4 cells at most.
	for (unsigned char a = 0; a < 4; a++)
	{
		short x = 0;
		short y = 0;

		switch (a)
		{
		case 0: //Top left cell
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(floor(cell_y));

			break;
		}
		case 1: //Top right cell
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(floor(cell_y));

			break;
		}
		case 2: //Bottom left cell
		{
			x = static_cast<short>(floor(cell_x));
			y = static_cast<short>(ceil(cell_y));

			break;
		}
		case 3: //Bottom right cell
		{
			x = static_cast<short>(ceil(cell_x));
			y = static_cast<short>(ceil(cell_y));
		}
		}

		//Making sure that the position is inside the map.
		if (0 <= x && 0 <= y && MAP_HEIGHT > y && MAP_WIDTH > x)
		{
				if (Cell::Wall == i_map[x][y])
				{
					output = 1;
				}
		}
	}

	return output;
}