#ifndef Functions_EaseOutElastic_H
#define Functions_EaseOutElastic_H

double EaseOutElastic(double value) {
	return value == 0 ? 0 : value == 1 ? 1 : pow(2, -10 * value) * sin((value * 10 - 0.75) * c4) + 1;
}

#endif
