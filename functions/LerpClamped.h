#ifndef Functions_LerpClamped_H
#define Functions_LerpClamped_H

double LerpClamped(double x, double y, double s) {
	return s < 0 ? x : s > 1 ? y : Lerp(x, y, s);
}

#endif
