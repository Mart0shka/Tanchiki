#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Global.hpp"
#include "Tank.hpp"
#include "MapCollision.hpp"
#include "Bullet.hpp"

Bullet::Bullet() :
	active(false),
	direction(4),
	position({ 0,0 }) {}


bool Bullet::get_active() {
	return active;
}

unsigned char Bullet::get_direction() {
	return direction;
}

void Bullet::set_direction(unsigned char tank_direction) {
    direction = tank_direction;
}

void Bullet::draw(sf::RenderWindow& window) {
	sf::Sprite sprite;

	sprite.setPosition(position.x, position.y);

	sf::Texture texture;

	if (!texture.loadFromFile("projectile.png"))
	{
		std::cerr << "failed to load image" << std::endl;
		exit(1);
	}

	sprite.setTexture(texture);

	window.draw(sprite);
}


void Bullet::set_active(bool i_active)
{
    active = i_active;

}

void Bullet::set_position(short i_x, short i_y)
{
    position = { i_x, i_y };
}

void Bullet::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
    if (active == 1) {
        std::array<bool, 5> walls{};
        walls[0] = map_collision(TANK_SPEED + position.x, position.y, i_map);
        walls[1] = map_collision(position.x, position.y - TANK_SPEED, i_map);
        walls[2] = map_collision(position.x - TANK_SPEED, position.y, i_map);
        walls[3] = map_collision(position.x, TANK_SPEED + position.y, i_map);
        walls[4] = map_collision(position.x, position.y, i_map);

        
        if (0 == walls[direction])
        {
            switch (direction)
            {
            case 0:
            {
                position.x += BULLET_SPEED;

                break;
            }
            case 1:
            {
                position.y -= BULLET_SPEED;

                break;
            }
            case 2:
            {
                position.x -= BULLET_SPEED;

                break;
            }
            case 3:
            {
                position.y += BULLET_SPEED;

                break;
            }
            }
            direction = 4;
            active = false;
        }

        if (-CELL_SIZE >= position.x)
        {
            position.x = CELL_SIZE * MAP_WIDTH - TANK_SPEED;
        }
        else if (CELL_SIZE * MAP_WIDTH <= position.x)
        {
            position.x = TANK_SPEED - CELL_SIZE;
        }
        std::cerr << position.x << "----" << position.y << "\n";
    }
}


Position Bullet::get_position()
{
    return position;
}



