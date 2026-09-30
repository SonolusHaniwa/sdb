#ifndef Functions_Multiply_H
#define Functions_Multiply_H

double Multiply(const vector<double> &value) {
	double res = 1;
	for (int i = 0; i < value.size(); i++) res *= value[i];
	return res;
}

#endif
