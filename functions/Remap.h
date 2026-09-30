#ifndef Functions_Remap_H
#define Functions_Remap_H

double Remap(double a, double b, double c, double d, double x) {
	return Lerp(c, d, (x - a) / (b - a));
}

#endif
