#ifndef Functions_EaseOutInQuint_H
#define Functions_EaseOutInQuint_H

double EaseOutInQuint(double value) {
	return value < 0.5 ? EaseOutQuint(value * 2) / 2 : EaseInQuint(value * 2 - 1) / 2 + 0.5;
}

#endif
