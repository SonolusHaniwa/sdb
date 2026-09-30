#ifndef Functions_EaseInOutCirc_H
#define Functions_EaseInOutCirc_H

double EaseInOutCirc(double value) {
	return value < 0.5 ? EaseInCirc(value * 2) / 2 : EaseOutCirc(value * 2 - 1) / 2 + 0.5;
}

#endif
