#ifndef Functions_IncrementPostPointed_H
#define Functions_IncrementPostPointed_H

double IncrementPostPointed(double id, double index, double offset) {
	return IncrementPost(Get(id, index), Get(id, index + 1) + offset);
}

#endif
