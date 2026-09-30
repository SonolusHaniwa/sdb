#ifndef Functions_DecrementPreShifted_H
#define Functions_DecrementPreShifted_H

double DecrementPreShifted(double id, double x, double y, double s) {
	return DecrementPre(id, x + y * s);
}

#endif
