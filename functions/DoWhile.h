#ifndef Functions_DoWhile_H
#define Functions_DoWhile_H

double DoWhile(double body, double test) {
	do {
		if (breakCount) return 0;
		RunCode(body);
		if (breakCount) return 0;
	} while(RunCode(test));
	return 0;
}

#endif
