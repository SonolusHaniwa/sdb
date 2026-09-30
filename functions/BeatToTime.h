#ifndef Functions_BeatToTime_H
#define Functions_BeatToTime_H

double BeatToTime(double beat) {
	BPM item = (*--upper_bound(bpmList.begin(), bpmList.end(), beat, [&](double b, BPM a) {
		return b < a.startBeat;
	}));
	return item.startTime + (beat - item.startBeat) / item.bpm * 60;
}

#endif
