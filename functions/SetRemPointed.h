#ifndef Functions_SetRemPointed_H
#define Functions_SetRemPointed_H

double SetRemPointed(double id, double index, double offset, double value) {
	return SetRem(Get(id, index), Get(id, index + 1) + offset, value);
}

#endif
