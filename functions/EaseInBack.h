#ifndef Functions_EaseInBack_H
#define Functions_EaseInBack_H

double EaseInBack(double value) {
	return c3 * value * value * value - c1 * value * value;
}

#endif
