#ifndef Functions_SetSubtractShifted_H
#define Functions_SetSubtractShifted_H

double SetSubtractShifted(double id, double x, double y, double s, double value) {
	return SetSubtract(id, x + y * s, value);
}

#endif
