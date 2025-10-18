#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <memory>
#include <cmath>

#include "shape.hpp"

void test_collision(Cup& cup, FallingShape& shape) {
	if (!shape.caught && is_intersecting(cup, shape)) {
		shape.caught = true;
	}
}

static constexpr size_t WINDOW_HEIGHT = 800;	// px
static constexpr size_t WINDOW_WIDTH = 600;		// px

int main(int argc, char **argv) {
	sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "falling blocks");
	window.setFramerateLimit(60);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> color_dist(0, colors.size() - 1);
	std::uniform_int_distribution<int> shape_dist(0, 2);
	int frame_count = 0;
	int spawn_interval = 60;
	float min_speed = 2.0f;
	float max_speed = 4.0f;
	float min_size = 20.0f;
	float max_size = 40.0f;
	int score = 0;

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

		if (++frame_count >= spawn_interval) {
			std::uniform_real_distribution<float> speed_dist(min_speed, max_speed);
			std::uniform_real_distribution<float> size_dist(min_size, max_size);
			
			float size = size_dist(gen);
			float x_pos = std::uniform_real_distribution<float>(size / 2.f, WINDOW_WIDTH - size / 2.f)(gen);
			sf::Color color = colors[color_dist(gen)];
			float speed = speed_dist(gen);
			
			int shape_type = shape_dist(gen);
			if (shape_type == 0)
				shapes.push_back(std::make_unique<FallingCircle>(x_pos, -size, size, color, speed));
			else if (shape_type == 1)
				shapes.push_back(std::make_unique<FallingRectangle>(x_pos, -size, size, color, speed));
			else
				shapes.push_back(std::make_unique<FallingTriangle>(x_pos, -size, size, color, speed));
			
			frame_count = 0;
		}

		player.update();

		// Update shapes and test collisions
		for (auto& shape : shapes) {
			if (!shape->caught) {
				shape->update();
				test_collision(cup, *shape);
				if (shape->caught) {
					score++;
				}
			}
		}

		// Remove shapes that fell off screen or were caught
		shapes.erase(
			std::remove_if(shapes.begin(), shapes.end(),
				[](const std::unique_ptr<FallingShape>& s) { 
					return s->caught || s->bottom() > WINDOW_HEIGHT; 
				}),
			shapes.end()
		);

		// Draw cup
		window.draw(cup.shape);

		// Draw shapes
		for (auto& shape : shapes) {
			shape->draw(window);
		}

		// xxx GameObject update

		// handle collisions

		
		// update game state

		// draw all shapes

		window.display();	// render
	}


	return 0;
}
