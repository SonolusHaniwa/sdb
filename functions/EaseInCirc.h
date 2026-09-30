#ifndef Functions_EaseInCirc_H
#define Functions_EaseInCirc_H

double EaseInCirc(double value) {
	return 1 - sqrt(1 - value * value);
}

#endif
