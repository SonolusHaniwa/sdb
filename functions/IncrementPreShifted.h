#ifndef Functions_IncrementPreShifted_H
#define Functions_IncrementPreShifted_H

double IncrementPreShifted(double id, double x, double y, double s) {
	return IncrementPre(id, x + y * s);
}

#endif
