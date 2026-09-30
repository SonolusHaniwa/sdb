#ifndef Functions_EaseOutInQuart_H
#define Functions_EaseOutInQuart_H

double EaseOutInQuart(double value) {
	return value < 0.5 ? EaseOutQuart(value * 2) / 2 : EaseInQuart(value * 2 - 1) / 2 + 0.5;
}

#endif
