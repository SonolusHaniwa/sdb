#ifndef Functions_RandomInteger_H
#define Functions_RandomInteger_H

double RandomInteger(double min, double max) {
	int val = Random(min, max);
	if (val < min) val = Ceil(min);
	if (val > max) val = Floor(max);
	return val;
}

#endif
