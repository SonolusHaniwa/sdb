#ifndef Functions_SetAddShifted_H
#define Functions_SetAddShifted_H

double SetAddShifted(double id, double x, double y, double s, double value) {
	return SetAdd(id, x + y * s, value);
}

#endif
