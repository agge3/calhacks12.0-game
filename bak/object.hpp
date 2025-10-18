#pragma once

#include <SFML/Graphics.hpp>

constexpr float player_width{60.f}, player_height{20.f}, player_velocity{8.f};

enum Object {
	PLAYER = 1,
	RAIN = 2,
	POSION = 3
}

struct Basket {
	RectangleShape shape;
	Vector2f velocity;
	Object obj_type;
	int coins_count = 0;
	int hearts = 3;

	Basket(float m_x, float m_y) {
		shape.setPosition(m_x, m_y);
		shape.setSize({player_width, player_height});
		shape.setFillColor(Color::Brown);
		shape.setOrigin(player_width / 2.f, player_height / 2.f);

		obj_type = PLAYER;
	}

	void update() {
		shape.move(velocity);
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) {
			velocity.x = -player_velocity;
		} else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < 800) {
			velocity.x = player_velocity;
		} else {
			velocity.x = 0;
		}
	}

	Object type() const {
		return obj_type;
	}

	sf::Vector2f location() const {
		return shape.getPosition();
	}

	void add_coins(int amount) {
		coins_count += amount;
	}

	void update_health(int amount) {
		hearts += amount;
	}

	int get_coins() {
		return coins_count;
	}

	bool is_alive() {
		return hearts == 0;
	}

	float left() const { return shape.getPosition().x - player_width / 2.f; }
    float right() const { return shape.getPosition().x + player_width / 2.f; }
};
