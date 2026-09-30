#ifndef Functions_SetMultiplyPointed_H
#define Functions_SetMultiplyPointed_H

double SetMultiplyPointed(double id, double index, double offset, double value) {
	return SetMultiply(Get(id, index), Get(id, index + 1) + offset, value);
}

#endif
