#ifndef Functions_EaseOutCubic_H
#define Functions_EaseOutCubic_H

double EaseOutCubic(double value) {
	return 1 - pow(1 - value, 3);
}

#endif
