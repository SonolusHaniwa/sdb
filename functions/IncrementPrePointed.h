#ifndef Functions_IncrementPrePointed_H
#define Functions_IncrementPrePointed_H

double IncrementPrePointed(double id, double index, double offset) {
	return IncrementPre(Get(id, index), Get(id, index + 1) + offset);
}

#endif
