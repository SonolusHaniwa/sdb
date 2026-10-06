#ifndef Functions_UnlerpClamped_H
#define Functions_UnlerpClamped_H

double UnlerpClamped(double a, double b, double x) {
	double value = Unlerp(a, b, x);
	return value < 0 ? 0 : (value > 1 ? 1 : value);
}

#endif
