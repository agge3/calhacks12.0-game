#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

static constexpr size_t WINDOW_HEIGHT = 800;	// px
static constexpr size_t WINDOW_WIDTH = 600;		// px

class Shape {
};



int main(int argc, char **argv) {
	sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "falling blocks");
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		while (auto ev = window.pollEvent()) {
			if (ev->is<sf::Event::Closed>()) {
				window.close();
			}
			if (ev->is<sf::Event::KeyPressed>()) {
				window.close();
			}
		}
		window.clear(sf::Color::Black);

		// xxx GameObject update

		// handle collisions

		
		// update game state

		// draw all shapes

		window.display();	// render
	}


	return 0;
}
