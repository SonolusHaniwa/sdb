#ifndef Functions_IncrementPost_H
#define Functions_IncrementPost_H

double IncrementPost(double id, double index) {
	Set(id, index, Get(id, index) + 1);
	return Get(id, index);
}

#endif
