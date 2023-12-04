#pragma once
#include "Bullet.hpp"

class Tank {
private:

	bool dead;

	unsigned char direction;

	Position position;

	bool stop;


	

public:
	Bullet bullet;
	Tank();

	bool get_stop();
	bool get_dead();
	Bullet get_bullet();

	unsigned char get_direction();

	void draw(sf::RenderWindow& window);
	void set_stop(bool i_stop);
	void set_dead(bool dead);
	void set_position(short x, short y);
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& map, float dt);
	void launch();

	Position get_position();
};