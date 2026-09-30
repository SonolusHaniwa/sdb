#ifndef Functions_Rem_H
#define Functions_Rem_H

double Rem(const vector<double> &value) {
	double res = value[0];
	vector<double> values = { 0, 0 };
	for (int i = 1; i < value.size(); i++) values[0] = res, values[1] = value[i], res = (res * value[i] > 0 ? 1 : -1) * Mod(values);
	return res;
}

#endif
