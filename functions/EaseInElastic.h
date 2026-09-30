#ifndef Functions_EaseInElastic_H
#define Functions_EaseInElastic_H

double EaseInElastic(double value) {
	return value == 0 ? 0 : value == 1 ? 1 : -pow(2, 10 * value - 10) * sin((value * 10 - 10.75) * c4);
}

#endif
