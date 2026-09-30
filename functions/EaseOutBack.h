#ifndef Functions_EaseOutBack_H
#define Functions_EaseOutBack_H

double EaseOutBack(double value) {
	return 1 + c3 * pow(value - 1, 3) + c1 * pow(value - 1, 2);
}

#endif
