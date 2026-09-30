#ifndef Functions_Subtract_H
#define Functions_Subtract_H

double Subtract(const vector<double> &value) {
	double res = value[0];
	for (int i = 1; i < value.size(); i++) res -= value[i];
	return res;
}

#endif
