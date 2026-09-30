#ifndef Functions_SetPointed_H
#define Functions_SetPointed_H

double SetPointed(double id, double index, double offset, double value) {
	return Set(Get(id, index), Get(id, index + 1) + offset, value);
}

#endif
