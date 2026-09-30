#ifndef Functions_Judge_H
#define Functions_Judge_H

double Judge(double source, double target, Judge_Group_min_max perfect, Judge_Group_min_max great, Judge_Group_min_max good) {
	if (perfect.min <= source - target && source - target <= perfect.max) return 1;
	if (great.min <= source - target && source - target <= great.max) return 2;
	if (good.min <= source - target && source - target <= good.max) return 3;
	return 0;
}

#endif
