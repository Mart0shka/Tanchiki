#pragma once

class Tank {
private:

	bool dead;

	unsigned char direction;

	Position position;

public:
	Tank();
	
	bool get_dead();

	unsigned char get_direction();

	void draw(sf::RenderWindow& window);
	void reset();
	void set_dead(bool dead);
	void set_position(short x, short y);
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& map);

	Position get_position();
};