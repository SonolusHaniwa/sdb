#ifndef Functions_EaseInOutCubic_H
#define Functions_EaseInOutCubic_H

double EaseInOutCubic(double value) {
	return value < 0.5 ? EaseInCubic(value * 2) / 2 : EaseOutCubic(value * 2 - 1) / 2 + 0.5;
}

#endif
