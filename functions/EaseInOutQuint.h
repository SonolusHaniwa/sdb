#ifndef Functions_EaseInOutQuint_H
#define Functions_EaseInOutQuint_H

double EaseInOutQuint(double value) {
	return value < 0.5 ? EaseInQuint(value * 2) / 2 : EaseOutQuint(value * 2 - 1) / 2 + 0.5;
}

#endif
