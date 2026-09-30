#ifndef Functions_SetDivideShifted_H
#define Functions_SetDivideShifted_H

double SetDivideShifted(double id, double x, double y, double s, double value) {
	return SetDivide(id, x + y * s, value);
}

#endif
