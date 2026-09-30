#ifndef Functions_EaseOutQuint_H
#define Functions_EaseOutQuint_H

double EaseOutQuint(double value) {
	return 1 - pow(1 - value, 5);
}

#endif
