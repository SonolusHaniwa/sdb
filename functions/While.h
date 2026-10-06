#ifndef Functions_While_H
#define Functions_While_H

double While(double test, double body) {
	updateCurrParam(0);
	while (RunCode(test)) {
		if (breakCount) return 0;
		updateCurrParam(1);
		RunCode(body);
		if (breakCount) return 0;
		updateCurrParam(0);
	}
	return 0;
}

#endif
