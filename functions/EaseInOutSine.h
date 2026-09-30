#ifndef Functions_EaseInOutSine_H
#define Functions_EaseInOutSine_H

double EaseInOutSine(double value) {
	return value < 0.5 ? EaseInSine(value * 2) / 2 : EaseOutSine(value * 2 - 1) / 2 + 0.5;
}

#endif
