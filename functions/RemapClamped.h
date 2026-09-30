#ifndef Functions_RemapClamped_H
#define Functions_RemapClamped_H

double RemapClamped(double a, double b, double c, double d, double x) {
	return LerpClamped(c, d, (x - a) / (b - a));
}

#endif
