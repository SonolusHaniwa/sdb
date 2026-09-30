#ifndef Functions_UnlerpClamped_H
#define Functions_UnlerpClamped_H

double UnlerpClamped(double a, double b, double x) {
	return x < a ? 0 : x > b ? 1 : Unlerp(a, b, x);
}

#endif
