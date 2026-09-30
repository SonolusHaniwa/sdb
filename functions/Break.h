#ifndef Functions_Break_H
#define Functions_Break_H

double Break(double count, double value) {
	int tmpCount = RunCode(count);
	if (breakCount) return 0;
	double tmpValue = RunCode(value);
	if (breakCount) return 0;
	breakCount = tmpCount;
	breakValue = tmpValue;
	return 0;
}

#endif
