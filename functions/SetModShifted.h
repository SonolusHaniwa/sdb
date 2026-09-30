#ifndef Functions_SetModShifted_H
#define Functions_SetModShifted_H

double SetModShifted(double id, double x, double y, double s, double value) {
	return SetMod(id, x + y * s, value);
}

#endif
