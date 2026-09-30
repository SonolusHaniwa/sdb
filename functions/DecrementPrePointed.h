#ifndef Functions_DecrementPrePointed_H
#define Functions_DecrementPrePointed_H

double DecrementPrePointed(double id, double index, double offset) {
	return DecrementPre(Get(id, index), Get(id, index + 1) + offset);
}

#endif
