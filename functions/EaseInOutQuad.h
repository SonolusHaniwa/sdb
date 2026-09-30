#ifndef Functions_EaseInOutQuad_H
#define Functions_EaseInOutQuad_H

double EaseInOutQuad(double value) {
	return value < 0.5 ? EaseInQuad(value * 2) / 2 : EaseOutQuad(value * 2 - 1) / 2 + 0.5;
}

#endif
