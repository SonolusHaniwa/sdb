#ifndef Functions_Add_H
#define Functions_Add_H

double Add(const vector<double> &value) {
	double res = 0;
	for (int i = 0; i < value.size(); i++) res += value[i];
	return res;
}

#endif
