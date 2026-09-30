#ifndef Functions_EaseOutExpo_H
#define Functions_EaseOutExpo_H

double EaseOutExpo(double value) {
	return value == 1 ? 1 : 1 - pow(2, -10 * value);
}

#endif
