#ifndef Functions_Divide_H
#define Functions_Divide_H

double Divide(const vector<double> &value) {
	double res = value[0];
	for (int i = 1; i < value.size(); i++) res /= value[i];
	return res;
}

#endif
