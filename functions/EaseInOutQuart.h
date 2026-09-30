#ifndef Functions_EaseInOutQuart_H
#define Functions_EaseInOutQuart_H

double EaseInOutQuart(double value) {
	return value < 0.5 ? EaseInQuart(value * 2) / 2 : EaseOutQuart(value * 2 - 1) / 2 + 0.5;
}

#endif
