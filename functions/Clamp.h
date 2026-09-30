#ifndef Functions_Clamp_H
#define Functions_Clamp_H

double Clamp(double x, double a, double b) {
	return x < a ? a : x > b ? b : x;
}

#endif
