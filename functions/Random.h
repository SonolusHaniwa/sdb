#ifndef Functions_Random_H
#define Functions_Random_H

double Random(double min, double max) {
	return 1.0 * rand() / RAND_MAX * (max - min) + min;
}

#endif
