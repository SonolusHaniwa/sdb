#ifndef Functions_DecrementPostPointed_H
#define Functions_DecrementPostPointed_H

double DecrementPostPointed(double id, double index, double offset) {
	return DecrementPost(Get(id, index), Get(id, index + 1) + offset);
}

#endif
