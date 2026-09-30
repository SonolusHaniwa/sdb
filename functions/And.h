#ifndef Functions_And_H
#define Functions_And_H

double And(const vector<double> &value) {
	for (int i = 0; i < value.size(); i++) {
		double res = RunCode(value[i]);
		if (res == 0) return 0;
		if (breakCount) return 0;
	}
	return 1;
}

#endif
