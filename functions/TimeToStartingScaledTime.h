#ifndef Functions_TimeToStartingScaledTime_H
#define Functions_TimeToStartingScaledTime_H

double TimeToStartingScaledTime(double time) {
	if (time < 0) return 0;
	return (*--upper_bound(timeScaleList.begin(), timeScaleList.end(), time, [](double b, TimeScale a){
		return b < a.startTime;
	})).startScaledTime;
}

#endif
