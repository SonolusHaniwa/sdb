#ifndef Functions_SetDivide_H
#define Functions_SetDivide_H

double SetDivide(double id, double index, double value) {
	return Set(id, index, Get(id, index) / value);
}

#endif
