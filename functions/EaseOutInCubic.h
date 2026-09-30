#ifndef Functions_EaseOutInCubic_H
#define Functions_EaseOutInCubic_H

double EaseOutInCubic(double value) {
	return value < 0.5 ? EaseOutCubic(value * 2) / 2 : EaseInCubic(value * 2 - 1) / 2 + 0.5;
}

#endif
