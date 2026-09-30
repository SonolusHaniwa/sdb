#ifndef Functions_EaseOutInExpo_H
#define Functions_EaseOutInExpo_H

double EaseOutInExpo(double value) {
	return value < 0.5 ? EaseOutExpo(value * 2) / 2 : EaseInExpo(value * 2 - 1) / 2 + 0.5;
}

#endif
