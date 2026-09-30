#ifndef Functions_SetSubtract_H
#define Functions_SetSubtract_H

double SetSubtract(double id, double index, double value) {
	return Set(id, index, Get(id, index) - value);
}

#endif
