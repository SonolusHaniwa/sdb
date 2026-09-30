#ifndef Functions_Mod_H
#define Functions_Mod_H

double Mod(const vector<double> &value) {
	double res = value[0];
	for (int i = 1; i < value.size(); i++) res -= Floor(res / value[i]) * value[i];
	return res;
}

#endif
