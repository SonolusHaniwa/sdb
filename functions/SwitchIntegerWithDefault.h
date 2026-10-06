#ifndef Functions_SwitchIntegerWithDefault_H
#define Functions_SwitchIntegerWithDefault_H

double SwitchIntegerWithDefault(double discriminant, const vector<double> &consequent, double default) {
	updateCurrParam(0);
	int d = RunCode(discriminant);
	if (breakCount) return 0;
	if (d < 0 || d >= consequent.size()) {
		updateCurrParam(1 + consequent.size());
		double res = RunCode(default);
		if (breakCount) return 0;
		return res;
	}
	updateCurrParam(1 + d);
	double res = RunCode(consequent[d]);
	if (breakCount) return 0;
	return res;
}

#endif
