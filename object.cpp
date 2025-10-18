#pragma once

#include <SFML/Graphics.hpp>

constexpr float player_width{60.f}, player_height{20.f}, player_velocity{8.f};

Enum Object {
	PLAYER = 1;
	
}

Struct Basket {
	RectangleShape shape;
	Vector2f velocity;

	Basket(float m_x, float m_y) {
		shape.setPosition(m_x, m_y);
		shape.setSize({player_width, player_height});
		shape.setFillColor(Color::Brown);
		shape.setOrigin(player_width / 2.f, player_height / 2.f);
	}

	void update() {
		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) {
			velocity.x = -player_velocity;
		} else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < 800) {
			velocity.x = player_velocity;
		} else {
			velocity.x = 0;
		}
	}

	void type() {
		return 
	}

	int coins;
	int hearts;
}
