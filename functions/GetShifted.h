#ifndef Functions_GetShifted_H
#define Functions_GetShifted_H

double GetShifted(double id, double x, double y, double s) {
	return Get(id, x + y * s);
}

#endif
