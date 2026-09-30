#ifndef Functions_SetDividePointed_H
#define Functions_SetDividePointed_H

double SetDividePointed(double id, double index, double offset, double value) {
	return SetDivide(Get(id, index), Get(id, index + 1) + offset, value);
}

#endif
