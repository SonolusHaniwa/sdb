#ifndef Functions_DecrementPre_H
#define Functions_DecrementPre_H

double DecrementPre(double id, double index) {
	double value = Get(id, index);
	Set(id, index, value - 1);
	return value;
}

#endif
