#ifndef Functions_SwitchWithDefault_H
#define Functions_SwitchWithDefault_H

double SwitchWithDefault(double discriminant, const vector<SwitchWithDefault_Group_test_consequent> &test_consequent, double default) {
	double d = RunCode(discriminant);
	if (breakCount) return 0;
	for (int i = 0; i < test_consequent.size(); i++) {
		double test = RunCode(test_consequent[i].test);
		if (breakCount) return 0;
		if (d == test) {
			double res = RunCode(test_consequent[i].consequent);
			if (breakCount) return 0;
			return res;
		}
	}
	double res = RunCode(default);
	if (breakCount) return 0;
	return res;
}

#endif
