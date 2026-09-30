#ifndef Functions_EaseInOutExpo_H
#define Functions_EaseInOutExpo_H

double EaseInOutExpo(double value) {
	return value < 0.5 ? EaseInExpo(value * 2) / 2 : EaseOutExpo(value * 2 - 1) / 2 + 0.5;
}

#endif
