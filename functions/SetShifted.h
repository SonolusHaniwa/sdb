#ifndef Functions_SetShifted_H
#define Functions_SetShifted_H

double SetShifted(double id, double x, double y, double s, double value) {
	return Set(id, x + y * s, value);
}

#endif
