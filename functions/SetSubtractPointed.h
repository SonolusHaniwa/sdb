#ifndef Functions_SetSubtractPointed_H
#define Functions_SetSubtractPointed_H

double SetSubtractPointed(double id, double index, double offset, double value) {
	return SetSubtract(Get(id, index), Get(id, index + 1) + offset, value);
}

#endif
