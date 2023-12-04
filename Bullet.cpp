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
        std::cerr << "failed to load image bullet" << std::endl;
        exit(1);
    }

    sprite.setTexture(texture);
    if(active) window.draw(sprite);
}


void Bullet::set_active(bool i_active)
{
    active = i_active;

}

void Bullet::set_position(short i_x, short i_y)
{
    position = { i_x, i_y };
}

void Bullet::update(std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, float dt)
{
    if (active == 1) {

        std::array<bool, 4> walls{};
        walls[0] = map_collision(BULLET_SPEED * dt + position.x, position.y, i_map);
        walls[1] = map_collision(position.x, position.y - BULLET_SPEED * dt, i_map);
        walls[2] = map_collision(position.x - BULLET_SPEED * dt, position.y, i_map);
        walls[3] = map_collision(position.x, BULLET_SPEED * dt + position.y, i_map);


        if (0 == walls[direction])
        {
            switch (direction)
            {
            case 0:
            {
                position.x += BULLET_SPEED * dt * 2;

                break;
            }
            case 1:
            {
                position.y -= BULLET_SPEED * dt;

                break;
            }
            case 2:
            {
                position.x -= BULLET_SPEED * dt;

                break;
            }
            case 3:
            {
                position.y += BULLET_SPEED * dt * 2;

                break;
            }
            }

        }
        else active = false;

        if (-CELL_SIZE >= position.x)
        {
            active = false;
            position.x = CELL_SIZE * MAP_WIDTH - TANK_SPEED;
        }
        else if (CELL_SIZE * MAP_WIDTH <= position.x)
        {
            active = false;
            position.x = TANK_SPEED - CELL_SIZE;
        }
        std::cerr << position.x << "----" << position.y << "\n";
    }
}


Position Bullet::get_position()
{
    return position;
}