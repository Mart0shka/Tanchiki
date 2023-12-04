#pragma once

class Bullet {
public:

	bool active;

	unsigned char direction;

	Position position;

	sf::Time time;

	Bullet();

	bool get_active();

	unsigned char get_direction();

	void draw(sf::RenderWindow& window);
	//void reset();
	void set_direction(unsigned char tank_direction);
	void set_active(bool active);
	void set_position(short x, short y);
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& map, float);

	Position get_position();

};