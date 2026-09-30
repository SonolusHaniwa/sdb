#ifndef Functions_TimeToScaledTime_H
#define Functions_TimeToScaledTime_H

double TimeToScaledTime(double time) {
	if (time < 0) return time;
	TimeScale item = *--upper_bound(timeScaleList.begin(), timeScaleList.end(), time, [](double b, TimeScale a){
		return b < a.startTime;
	});
	// cout << time << " " << item.startScaledTime << " " << (time - item.startTime) * item.scaledValue << endl;
	return item.startScaledTime + (time - item.startTime) * item.scaledValue;
}

#endif
