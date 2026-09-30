#ifndef Functions_While_H
#define Functions_While_H

double While(double test, double body) {
	while (RunCode(test)) {
		if (breakCount) return 0;
		RunCode(body);
		if (breakCount) return 0;
	}
	return 0;
}

#endif
