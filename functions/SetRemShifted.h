#ifndef Functions_SetRemShifted_H
#define Functions_SetRemShifted_H

double SetRemShifted(double id, double x, double y, double s, double value) {
	return SetRem(id, x + y * s, value);
}

#endif
