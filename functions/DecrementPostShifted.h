#ifndef Functions_DecrementPostShifted_H
#define Functions_DecrementPostShifted_H

double DecrementPostShifted(double id, double x, double y, double s) {
	return DecrementPost(id, x + y * s);
}

#endif
