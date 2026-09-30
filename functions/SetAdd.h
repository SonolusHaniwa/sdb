#ifndef Functions_SetAdd_H
#define Functions_SetAdd_H

double SetAdd(double id, double index, double value) {
	return Set(id, index, Get(id, index) + value);
}

#endif
