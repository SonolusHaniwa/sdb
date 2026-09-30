#ifndef Functions_SetMultiply_H
#define Functions_SetMultiply_H

double SetMultiply(double id, double index, double value) {
	return Set(id, index, Get(id, index) * value );
}

#endif
