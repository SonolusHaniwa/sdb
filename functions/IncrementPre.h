#ifndef Functions_IncrementPre_H
#define Functions_IncrementPre_H

double IncrementPre(double id, double index) {
	double value = Get(id, index);
	Set(id, index, value + 1);
	return value;
}

#endif
