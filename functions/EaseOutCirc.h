#ifndef Functions_EaseOutCirc_H
#define Functions_EaseOutCirc_H

double EaseOutCirc(double value) {
	return sqrt(1 - pow(value - 1, 2));
}

#endif
