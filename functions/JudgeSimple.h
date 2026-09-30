#ifndef Functions_JudgeSimple_H
#define Functions_JudgeSimple_H

double JudgeSimple(double source, double target, double perfect, double great, double good) {
	return Judge(source, target, { -perfect, perfect }, { -great, great }, { -good, good });
}

#endif
