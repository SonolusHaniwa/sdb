#ifndef Functions_EaseInSine_H
#define Functions_EaseInSine_H

double EaseInSine(double value) {
	return 1 - cos((value * PI) / 2);
}

#endif
