#ifndef Functions_EaseOutQuart_H
#define Functions_EaseOutQuart_H

double EaseOutQuart(double value) {
	return 1 - pow(1 - value, 4);
}

#endif
