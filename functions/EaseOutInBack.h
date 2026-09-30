#ifndef Functions_EaseOutInBack_H
#define Functions_EaseOutInBack_H

double EaseOutInBack(double value) {
	return value < 0.5 ? EaseOutBack(value * 2) / 2 : EaseInBack(value * 2 - 1) / 2 + 0.5;
}

#endif
