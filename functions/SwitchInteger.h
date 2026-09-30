#ifndef Functions_SwitchInteger_H
#define Functions_SwitchInteger_H

double SwitchInteger(double discriminant, const vector<double> &consequent) {
	int d = RunCode(discriminant);
	if (breakCount) return 0;
	// for (int i = 0; i < consequent.size(); i++) {
	if (d < 0 || d >= consequent.size()) return 0;
	double res = RunCode(consequent[d]);
	if (breakCount) return 0;
	return res;
	// }
	return 0;
}

#endif
