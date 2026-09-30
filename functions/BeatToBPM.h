#ifndef Functions_BeatToBPM_H
#define Functions_BeatToBPM_H

double BeatToBPM(double beat) {
	return (*--upper_bound(bpmList.begin(), bpmList.end(), beat, [&](double b, BPM a) {
		return b < a.startBeat;
	})).bpm;
}

#endif
