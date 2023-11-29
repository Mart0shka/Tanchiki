#include <SFML/Graphics.hpp>
#include <array>
#include <chrono>
#include <ctime>
#include <iostream>

#include "Global.hpp"
#include "ConvertSketch.hpp"
#include "Tank.hpp"
#include "DrawMap.hpp"
#include "MapCollision.hpp"


int main()
{


	//Similar to lag, used to make the game framerate-independent.
	std::chrono::time_point<std::chrono::steady_clock> previous_time;

	unsigned int lag = 0;

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

	//Get the current time and store it in a variable.
	previous_time = std::chrono::steady_clock::now();


    while (window.isOpen()){

		//Here we're calculating the lag.
		unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

		lag += delta_time;

		previous_time += std::chrono::microseconds(delta_time);
		
		while (FRAME_DURATION <= lag)
		{
			//We decrease the lag.
			lag -= FRAME_DURATION;

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
		}


		if (FRAME_DURATION > lag) {
			tank.update(map);
			if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
				tank.launch();
			}
			window.clear();
			draw_map(map, window);
			tank.draw(window);
			tank.get_bullet().draw(window);
		}
        window.display();
    }

    return 0;
}