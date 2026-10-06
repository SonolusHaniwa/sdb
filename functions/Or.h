#ifndef Functions_Or_H
#define Functions_Or_H

double Or(const vector<double> &value) {
	for (int i = 0; i < value.size(); i++) {
		updateCurrParam(i);
		double res = RunCode(value[i]);
		if (res == 1) return 1;
		if (breakCount) return 0;
	}
	return 0;
}

#endif
