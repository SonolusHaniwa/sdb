#ifndef Functions_SetModPointed_H
#define Functions_SetModPointed_H

double SetModPointed(double id, double index, double offset, double value) {
	return SetMod(Get(id, index), Get(id, index + 1) + offset, value);
}

#endif
