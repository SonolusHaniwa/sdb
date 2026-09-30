#ifndef Functions_Power_H
#define Functions_Power_H

double Power(const vector<double> &value) {
	double res = value[0];
	for (int i = 1; i < value.size(); i++) res = pow(res, value[i]);
	return res;
}

#endif
