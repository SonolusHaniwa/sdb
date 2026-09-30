#ifndef Functions_Lerp_H
#define Functions_Lerp_H

double Lerp(double x, double y, double s) {
	return x + (y - x) * s;
}

#endif
