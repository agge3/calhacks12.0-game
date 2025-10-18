#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

static constexpr size_t WINDOW_HEIGHT = 800;	// px
static constexpr size_t WINDOW_WIDTH = 600;	// px
using Win = sf::RenderWindow;

void handleInput();
void update(sf::Time dt);
void render(const Win &win) {
	win.clear(Color::Black);
	win.display();
}

int main(int argc, char **argv) {
	sf::RenderWindow window{{WINDOW_WIDTH, WINDOW_HEIGHT, "falling blocks"}};
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		handleInput();
		update(dt);
		render();
	}


	return 0;
}
