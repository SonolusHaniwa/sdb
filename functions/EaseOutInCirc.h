#ifndef Functions_EaseOutInCirc_H
#define Functions_EaseOutInCirc_H

double EaseOutInCirc(double value) {
	return value < 0.5 ? EaseOutCirc(value * 2) / 2 : EaseInCirc(value * 2 - 1) / 2 + 0.5;
}

#endif
