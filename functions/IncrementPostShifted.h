#ifndef Functions_IncrementPostShifted_H
#define Functions_IncrementPostShifted_H

double IncrementPostShifted(double id, double x, double y, double s) {
	return IncrementPost(id, x + y * s);
}

#endif
