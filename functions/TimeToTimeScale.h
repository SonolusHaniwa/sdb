#ifndef Functions_TimeToTimeScale_H
#define Functions_TimeToTimeScale_H

double TimeToTimeScale(double time) {
	if (time < 0) return 1;
	return (*--upper_bound(timeScaleList.begin(), timeScaleList.end(), time, [](double b, TimeScale a){
		return b < a.startTime;
	})).scaledValue;
}

#endif
