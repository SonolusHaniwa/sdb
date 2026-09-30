#ifndef Functions_SetMod_H
#define Functions_SetMod_H

double SetMod(double id, double index, double value) {
	vector<double> values = { Get(id, index), value };
	return Set(id, index, Mod(values));
}

#endif
