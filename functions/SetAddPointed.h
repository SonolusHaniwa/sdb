#ifndef Functions_SetAddPointed_H
#define Functions_SetAddPointed_H

double SetAddPointed(double id, double index, double offset, double value) {
	return SetAdd(Get(id, index), Get(id, index + 1) + offset, value);
}

#endif
