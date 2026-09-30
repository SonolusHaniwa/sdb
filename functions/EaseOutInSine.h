#ifndef Functions_EaseOutInSine_H
#define Functions_EaseOutInSine_H

double EaseOutInSine(double value) {
	return value < 0.5 ? EaseOutSine(value * 2) / 2 : EaseInSine(value * 2 - 1) / 2 + 0.5;
}

#endif
