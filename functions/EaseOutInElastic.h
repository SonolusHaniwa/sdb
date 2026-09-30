#ifndef Functions_EaseOutInElastic_H
#define Functions_EaseOutInElastic_H

double EaseOutInElastic(double value) {
	return value < 0.5 ? EaseOutElastic(value * 2) / 2 : EaseInElastic(value * 2 - 1) / 2 + 0.5;
}

#endif
