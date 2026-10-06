#ifndef Functions_SwitchWithDefault_H
#define Functions_SwitchWithDefault_H

double SwitchWithDefault(double discriminant, const vector<SwitchWithDefault_Group_test_consequent> &test_consequent, double default) {
	updateCurrParam(0);
	double d = RunCode(discriminant);
	if (breakCount) return 0;
	for (int i = 0; i < test_consequent.size(); i++) {
		updateCurrParam(2 * i + 1);
		double test = RunCode(test_consequent[i].test);
		if (breakCount) return 0;
		if (d == test) {
			updateCurrParam(2 * i + 2);
			double res = RunCode(test_consequent[i].consequent);
			if (breakCount) return 0;
			return res;
		}
	}
	updateCurrParam(1 + 2 * test_consequent.size());
	double res = RunCode(default);
	if (breakCount) return 0;
	return res;
}

#endif
