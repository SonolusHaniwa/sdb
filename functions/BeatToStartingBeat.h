#ifndef Functions_BeatToStartingBeat_H
#define Functions_BeatToStartingBeat_H

double BeatToStartingBeat(double beat) {
	return (*--upper_bound(bpmList.begin(), bpmList.end(), beat, [&](double b, BPM a) {
		return b < a.startBeat;
	})).startBeat;
}

#endif
