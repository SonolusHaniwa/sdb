#ifndef Functions_EaseInOutElastic_H
#define Functions_EaseInOutElastic_H

double EaseInOutElastic(double value) {
	return value < 0.5 ? EaseInElastic(value * 2) / 2 : EaseOutElastic(value * 2 - 1) / 2 + 0.5;
}

#endif
