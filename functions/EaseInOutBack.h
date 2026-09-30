#ifndef Functions_EaseInOutBack_H
#define Functions_EaseInOutBack_H

double EaseInOutBack(double value) {
	return value < 0.5 ? EaseInBack(value * 2) / 2 : EaseOutBack(value * 2 - 1) / 2 + 0.5;
}

#endif
