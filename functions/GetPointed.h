#ifndef Functions_GetPointed_H
#define Functions_GetPointed_H

double GetPointed(double id, double index, double offset) {
	return Get(Get(id, index), Get(id, index + 1) + offset);
}

#endif
