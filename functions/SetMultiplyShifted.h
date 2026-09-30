#ifndef Functions_SetMultiplyShifted_H
#define Functions_SetMultiplyShifted_H

double SetMultiplyShifted(double id, double x, double y, double s, double value) {
	return SetMultiply(id, x + y * s, value);
}

#endif
