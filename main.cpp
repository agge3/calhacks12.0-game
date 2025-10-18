#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <memory>
#include <cmath>

static constexpr size_t WINDOW_HEIGHT = 800;
static constexpr size_t WINDOW_WIDTH = 600;

// Game constants
constexpr float cup_width{80.f}, cup_height{20.f}, cup_velocity{6.f};

// Color palette
const std::vector<sf::Color> colors = {
	sf::Color::Red,
	sf::Color::Green,
	sf::Color::Blue,
	sf::Color::Yellow,
	sf::Color::Magenta,
	sf::Color::Cyan,
	sf::Color(255, 165, 0),  // Orange
	sf::Color(128, 0, 128)   // Purple
};

struct Cup {
	sf::RectangleShape shape;
	sf::Vector2f velocity;

	Cup(float m_x, float m_y) {
		shape.setPosition({m_x, m_y});
		shape.setSize({cup_width, cup_height});
		shape.setFillColor(sf::Color::White);
		shape.setOrigin({cup_width / 2.f, cup_height / 2.f});
	}

	void update() {
		shape.move(velocity);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0)
			velocity.x = -cup_velocity;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < WINDOW_WIDTH)
			velocity.x = cup_velocity;
		else
			velocity.x = 0;
	}

	float x() { return shape.getPosition().x; }
	float y() { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.f; }
	float right() { return x() + shape.getSize().x / 2.f; }
	float top() { return y() - shape.getSize().y / 2.f; }
	float bottom() { return y() + shape.getSize().y / 2.f; }
};

// Base interface for all falling shapes
struct FallingShape {
	float speed;
	float size;
	bool caught{false};

	virtual ~FallingShape() = default;
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual float x() = 0;
	virtual float y() = 0;
	virtual float left() = 0;
	virtual float right() = 0;
	virtual float top() = 0;
	virtual float bottom() = 0;
};

struct FallingCircle : FallingShape {
	sf::CircleShape shape;

	FallingCircle(float m_x, float m_y, float s, const sf::Color& color, float spd) {
		size = s;
		speed = spd;
		shape.setPosition({m_x, m_y});
		shape.setRadius(size / 2.f);
		shape.setFillColor(color);
		shape.setOrigin({size / 2.f, size / 2.f});
	}

	void update() override { shape.move({0, speed}); }
	void draw(sf::RenderWindow& window) override { window.draw(shape); }
	float x() override { return shape.getPosition().x; }
	float y() override { return shape.getPosition().y; }
	float left() override { return x() - size / 2.f; }
	float right() override { return x() + size / 2.f; }
	float top() override { return y() - size / 2.f; }
	float bottom() override { return y() + size / 2.f; }
};

struct FallingRectangle : FallingShape {
	sf::RectangleShape shape;

	FallingRectangle(float m_x, float m_y, float s, const sf::Color& color, float spd) {
		size = s;
		speed = spd;
		shape.setPosition({m_x, m_y});
		shape.setSize({size, size});
		shape.setFillColor(color);
		shape.setOrigin({size / 2.f, size / 2.f});
	}

	void update() override { shape.move({0, speed}); }
	void draw(sf::RenderWindow& window) override { window.draw(shape); }
	float x() override { return shape.getPosition().x; }
	float y() override { return shape.getPosition().y; }
	float left() override { return x() - size / 2.f; }
	float right() override { return x() + size / 2.f; }
	float top() override { return y() - size / 2.f; }
	float bottom() override { return y() + size / 2.f; }
};

struct FallingTriangle : FallingShape {
	sf::CircleShape shape;

	FallingTriangle(float m_x, float m_y, float s, const sf::Color& color, float spd) {
		size = s;
		speed = spd;
		shape.setPosition({m_x, m_y});
		shape.setRadius(size / 2.f);
		shape.setPointCount(3);
		shape.setFillColor(color);
		shape.setOrigin({size / 2.f, size / 2.f});
	}

	void update() override { shape.move({0, speed}); }
	void draw(sf::RenderWindow& window) override { window.draw(shape); }
	float x() override { return shape.getPosition().x; }
	float y() override { return shape.getPosition().y; }
	float left() override { return x() - size / 2.f; }
	float right() override { return x() + size / 2.f; }
	float top() override { return y() - size / 2.f; }
	float bottom() override { return y() + size / 2.f; }
};

template<typename T1, typename T2>
bool is_intersecting(T1& m_a, T2& m_b) {
	return m_a.right() >= m_b.left() && m_a.left() <= m_b.right()
		&& m_a.bottom() >= m_b.top() && m_a.top() <= m_b.bottom();
}

void test_collision(Cup& cup, FallingShape& shape) {
	if (!shape.caught && is_intersecting(cup, shape)) {
		shape.caught = true;
	}
}

int main(int argc, char **argv) {
	sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "falling blocks");
	window.setFramerateLimit(60);

	Cup cup{WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 50.f};
	std::vector<std::unique_ptr<FallingShape>> shapes;

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
				const auto* key_ev = ev->getIf<sf::Event::KeyPressed>();
				if (key_ev->code == sf::Keyboard::Key::Escape) {
					window.close();
				}
			}
		}

		window.clear(sf::Color::Black);

		// Increase difficulty over time
		if (score > 0 && score % 10 == 0) {
			spawn_interval = std::max(20, spawn_interval - 1);
			max_speed = std::min(8.0f, max_speed + 0.05f);
			min_speed = std::min(4.0f, min_speed + 0.02f);
		}

		// Spawn new shapes
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

		// Update cup
		cup.update();

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

		window.display();
	}

	return 0;
}
