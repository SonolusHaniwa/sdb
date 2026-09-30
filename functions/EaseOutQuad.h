#ifndef Functions_EaseOutQuad_H
#define Functions_EaseOutQuad_H

double EaseOutQuad(double value) {
	return 1 - (1 - value) * (1 - value);
}

#endif
