#ifndef Functions_SetPower_H
#define Functions_SetPower_H

double SetPower(double id, double index, double value) {
	vector<double> values = { Get(id, index), value };
	return Set(id, index, Power(values));
}

#endif
