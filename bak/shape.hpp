#include <SFML/System.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <memory>
#include <cmath>

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

enum class ShapeType {
	Circle,
	Rectangle,
	Triangle,
};

struct Shape {
	float speed;
	float size;
	bool caught = false;

	virtual ~Shape() = default;
	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual float x() = 0;
	virtual float y() = 0;
	virtual float left() = 0;
	virtual float right() = 0;
	virtual float top() = 0;
	virtual float bottom() = 0;
};

struct Rectangle : public Shape {
	sf::RectangleShape shape;
	Rectangle(float m_x, float m_y, float sz, const sf::Color& color, float speed) : sz(sz), speed(speed) {
		size = s;
		speed = spd;
		shape.setPosition(m_x, m_y);
		shape.setSize({size, size});
		shape.setFillColor(color);
		shape.setOrigin(size / 2.f, size / 2.f);
	}

	void update() override { shape.move(0, speed); }
	void draw(sf::RenderWindow& window) override { window.draw(shape); }
	float x() override { return shape.getPosition().x; }
	float y() override { return shape.getPosition().y; }
	float left() override { return x() - size / 2.f; }
	float right() override { return x() + size / 2.f; }
	float top() override { return y() - size / 2.f; }
	float bottom() override { return y() + size / 2.f; }
};

struct Circle : public Shape {
	sf::CircleShape shape;
	Circle(float m_x, float m_y, float s, const sf::Color& color, float spd) {
		size = s;
		speed = spd;
		shape.setPosition(m_x, m_y);
		shape.setRadius(size / 2.f);
		shape.setFillColor(color);
		shape.setOrigin(size / 2.f, size / 2.f);
	}

	void update() override { shape.move(0, speed); }
	void draw(sf::RenderWindow& window) override { window.draw(shape); }
	float x() override { return shape.getPosition().x; }
	float y() override { return shape.getPosition().y; }
	float left() override { return x() - size / 2.f; }
	float right() override { return x() + size / 2.f; }
	float top() override { return y() - size / 2.f; }
	float bottom() override { return y() + size / 2.f; }
};

struct Triangle : Shape {
	sf::CircleShape shape;

	Triangle(float m_x, float m_y, float s, const sf::Color& color, float spd) {
		size = s;
		speed = spd;
		shape.setPosition(m_x, m_y);
		shape.setRadius(size / 2.f);
		shape.setPointCount(3);
		shape.setFillColor(color);
		shape.setOrigin(size / 2.f, size / 2.f);
	}

	void update() override { shape.move(0, speed); }
	void draw(sf::RenderWindow& window) override { window.draw(shape); }
	float x() override { return shape.getPosition().x; }
	float y() override { return shape.getPosition().y; }
	float left() override { return x() - size / 2.f; }
	float right() override { return x() + size / 2.f; }
	float top() override { return y() - size / 2.f; }
	float bottom() override { return y() + size / 2.f; }
};
