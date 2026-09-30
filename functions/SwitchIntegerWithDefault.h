#ifndef Functions_SwitchIntegerWithDefault_H
#define Functions_SwitchIntegerWithDefault_H

double SwitchIntegerWithDefault(double discriminant, const vector<double> &consequent, double default) {
	int d = RunCode(discriminant);
	if (breakCount) return 0;
	if (d < 0 || d >= consequent.size()) {
		double res = RunCode(default);
		if (breakCount) return 0;
		return res;
	}
	double res = RunCode(consequent[d]);
	if (breakCount) return 0;
	return res;
}

#endif
