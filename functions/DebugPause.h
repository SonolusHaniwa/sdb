#ifndef Functions_DebugPause_H
#define Functions_DebugPause_H

double DebugPause() {
	shouldStop = forceStop = true;
	return 0;
}

#endif
