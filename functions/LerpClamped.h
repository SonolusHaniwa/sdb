#ifndef Functions_LerpClamped_H
#define Functions_LerpClamped_H

double LerpClamped(double x, double y, double s) {
	double value = Lerp(x, y, s);
	return value < 0 ? 0 : (value > 1 ? 1 : value);
}

#endif
