#include <SFML/Graphics.hpp>
#include <array>
#include <chrono>
#include <ctime>
#include <iostream>
#include<vector>

#include "Global.hpp"
#include "ConvertSketch.hpp"
#include "Tank.hpp"
#include "DrawMap.hpp"
#include "MapCollision.hpp"


int main()
{
	float shoot_delay = 30;
	
	bool can_launch = true;

	sf::Clock clock;

	std::array<std::string, MAP_HEIGHT> map_sketch1 = {

		" ################### ",
		" #        #        # ",
		" # ## ### # ### ## # ",
		" #                 # ",
		" # ## #  ###  # ## # ",
		" #    #   #   #    # ",
		" ###  ##  #  ##  ### ",
		" ###  #       #  ### ",
		" ###  # ## ## #  ### ",
		" #      #   #      # ",
		" ###  # ## ## #  ### ",
		"   #  #       #  #   ",
		" ###  # ##### #  ### ",
		" #        #        # ",
		" #    ##  #  ##    # ",
		" #  #     T     #  # ",
		" #  # # #   # # #  # ",
		" #    #   #   #    # ",
		" # #    # # #    # # ",
		" #                 # ",
		" ################### "

	};

	std::array<std::string, MAP_HEIGHT> map_sketch = {

		" ################### ",
		" #        #        # ",
		" #  #  ## #  ##  # # ",
		" #                 # ",
		" #  # #  ###  #  # # ",
		" #   #    #   #    # ",
		" #   #    #   #    # ",
		" #   #        #    # ",
		" #   #  #   # #    # ",
		" #      #   #      # ",
		" #      #   #      # ",
		" #                 # ",
		" ###    #####     ## ",
		" #      #   #      # ",
		" #   #  #   #  #   # ",
		" #        T        # ",
		" #                 # ",
		" #    ##    ##     # ",
		" #                 # ",
		" #                 # ",
		" ################### "

	};

	std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};


	sf::Event event;

	sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Tanchiki", sf::Style::Close);

	//Resizing the window.
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

	Tank tank;

	map = convert_sketch(map_sketch, tank);

	sf::Time dt = clock.restart();
	float reload = 0;
	while (window.isOpen()) {
		dt = clock.getElapsedTime();
		float dtAsMSec = dt.asMilliseconds();
		if (dtAsMSec > 15) {
			dtAsMSec /= 15;
			sf::Time dt = clock.restart();
		}
		else { continue; }


		while (1 == window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				//Making sure the player can close the window.
				window.close();
			}
			}
		}
	
		if (shoot_delay>=30 and 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			tank.launch();
			shoot_delay = 0;
		}

		window.clear();
		draw_map(map, window);

		tank.update(map, dtAsMSec);
		tank.draw(window);
		if (!tank.bullets.empty()) {
			for (int i = 0; i < tank.bullets.size(); ++i) {
				tank.bullets[i]->update(map, dtAsMSec); //суммируемс€ dt, и если какое-то большое, то прибовл€ем
				tank.bullets[i]->draw(window);
			}
		}
		shoot_delay += dtAsMSec;
		

		tank.kill_non_active_bullet();

		window.display();
	}

	return 0;
}



