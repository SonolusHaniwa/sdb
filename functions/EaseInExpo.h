#ifndef Functions_EaseInExpo_H
#define Functions_EaseInExpo_H

double EaseInExpo(double value) {
	return value == 0 ? 0 : pow(2, 10 * value - 10);
}

#endif
