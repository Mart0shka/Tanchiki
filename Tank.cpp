#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Global.hpp"
#include "Bullet.hpp"
#include "Tank.hpp"
#include "MapCollision.hpp"

Tank::Tank() :
	dead(0),
	direction(0),
	position({ 0,0 }) {}

bool Tank::get_dead() {
	return dead;
}

unsigned char Tank::get_direction(){
	return direction;
}

void Tank::draw(sf::RenderWindow& window) {
	sf::Sprite sprite;


	sprite.setPosition(position.x, position.y);

	sf::Texture texture;

    if (!texture.loadFromFile("test2.png"))
    {
        std::cerr << "failed to load image" << std::endl;
        exit(1);
    }

	sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, (CELL_SIZE * direction), CELL_SIZE, CELL_SIZE));


	window.draw(sprite);
}

void Tank::reset() {
	dead = 0;
	direction = 0;
}


void Tank::set_dead(bool i_dead)
{
	dead = i_dead;

}

void Tank::set_position(short i_x, short i_y)
{
	position = { i_x, i_y };
}

void Tank::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
    std::array<bool, 4> walls{};
    walls[0] = map_collision(TANK_SPEED + position.x, position.y, i_map);
    walls[1] = map_collision(position.x, position.y - TANK_SPEED, i_map);
    walls[2] = map_collision(position.x - TANK_SPEED, position.y, i_map);
    walls[3] = map_collision(position.x, TANK_SPEED + position.y, i_map);

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (0 == walls[0]) //You can't turn in this direction if there's a wall there.
        {
            direction = 0;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (0 == walls[1])
        {
            direction = 1;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (0 == walls[2])
        {
            direction = 2;
        }
    }

    if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (0 == walls[3])
        {
            direction = 3;
        }
    }

    if (0 == walls[direction])
    {
        switch (direction)
        {
        case 0:
        {
            position.x += TANK_SPEED;

            break;
        }
        case 1:
        {
            position.y -= TANK_SPEED;

            break;
        }
        case 2:
        {
            position.x -= TANK_SPEED;

            break;
        }
        case 3:
        {
            position.y += TANK_SPEED;
        }
        }
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


Position Tank::get_position()
{
	return position;
}

Bullet Tank::get_bullet()
{
    return bullet;
}

void Tank::launch() {
    bullet.set_direction(direction);
    bullet.set_active(true);
    bullet.set_position(position.x, position.y);
}