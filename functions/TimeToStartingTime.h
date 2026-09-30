#ifndef Functions_TimeToStartingTime_H
#define Functions_TimeToStartingTime_H

double TimeToStartingTime(double time) {
	if (time < 0) return 0;
	return (*--upper_bound(timeScaleList.begin(), timeScaleList.end(), time, [](double b, TimeScale a){
		return b < a.startTime;
	})).startTime;
}

#endif
