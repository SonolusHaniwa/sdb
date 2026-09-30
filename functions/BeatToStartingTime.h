#ifndef Functions_BeatToStartingTime_H
#define Functions_BeatToStartingTime_H

double BeatToStartingTime(double beat) {
	return (*--upper_bound(bpmList.begin(), bpmList.end(), beat, [&](double b, BPM a) {
		return b < a.startBeat;
	})).startTime;
}

#endif
