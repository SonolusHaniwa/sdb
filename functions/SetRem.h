#ifndef Functions_SetRem_H
#define Functions_SetRem_H

double SetRem(double id, double index, double value) {
	vector<double> values = { Get(id, index), value };
	return Set(id, index, Rem(values));
}

#endif
