#ifndef Functions_DecrementPost_H
#define Functions_DecrementPost_H

double DecrementPost(double id, double index) {
	Set(id, index, Get(id, index) - 1);
	return Get(id, index);
}

#endif
