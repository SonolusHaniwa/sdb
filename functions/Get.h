#ifndef Functions_Get_H
#define Functions_Get_H

double Get(double id, double index) {
	if (readMap[int(id)][callbackNameId] == 0) return throwError(), 0;
	if (overflowMemory(id, index)) return throwError(), 0;
	// if (int(id) >= 4000 && int(id) < 4100)
	// 	return generalMemory[int(id) + 100][int(index) + memorySize[int(id)] * entityId[gettid()]];
	return generalMemory[int(id)][int(index)];
}

#endif
