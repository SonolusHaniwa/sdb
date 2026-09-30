#ifndef Functions_EaseOutInQuad_H
#define Functions_EaseOutInQuad_H

double EaseOutInQuad(double value) {
	return value < 0.5 ? EaseOutQuad(value * 2) / 2 : EaseInQuad(value * 2 - 1) / 2 + 0.5;
}

#endif
