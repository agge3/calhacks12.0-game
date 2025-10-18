template<typename T1, typename T2>
bool intersect(T1 &obj1, T2 &obj2) {
	return obj1.location() == obj2.location();
}

// 1 == player
// 2 == object
template <typename T1, typename T2>
bool check_collision(T1 &obj1, T2 &obj2) {
	if (obj2.type() == POISON) {
		obj1.update_health(-1);
	} else if (obj2.type() == RAIN) {
		if (obj1.get_coins() >= 10) {
			obj1.life(1);
		}

		obj1.update_coins(1);
	}
}
