#ifndef Functions_Block_H
#define Functions_Block_H

double Block(double body) {
	double res = RunCode(body);
	if (breakCount) return breakCount--, breakValue;
	return res;
}

#endif
