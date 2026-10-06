#ifndef Functions_If_H
#define Functions_If_H

double If(double test, double consequent, double alternate) {
	updateCurrParam(0);
	bool res = RunCode(test);
	if (breakCount) return 0;
	double res2 = 0;
	if (res) {
		updateCurrParam(1);
		res2 = RunCode(consequent);
	}
	else {
		updateCurrParam(2);
		res2 = RunCode(alternate);
	}
	if (breakCount) return 0;
	return res2;
}

#endif
