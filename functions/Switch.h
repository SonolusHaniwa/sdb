#ifndef Functions_Switch_H
#define Functions_Switch_H

double Switch(double discriminant, const vector<Switch_Group_test_consequent> &test_consequent) {
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
	return 0;
}

#endif
