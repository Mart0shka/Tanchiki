#pragma once
#include "Bullet.hpp"
#include <vector>

class Tank {
private:

	bool dead;

	unsigned char direction;

	Position position;

	bool stop;


public:

	std::vector <Bullet*> bullets;

	Tank();

	bool get_stop();
	bool get_dead();
	Bullet* get_bullet(int i);

	unsigned char get_direction();

	void draw(sf::RenderWindow& window);
	void set_stop(bool i_stop);
	void set_dead(bool dead);
	void set_position(short x, short y);
	void update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& map, float dt);
	void launch();
	void kill_non_active_bullet();

	Position get_position();
};