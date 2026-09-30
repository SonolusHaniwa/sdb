#ifndef Functions_Set_H
#define Functions_Set_H

double Set(double id, double index, double value) {
	// cout << id << " " << callbackNameId << " " << writeMap[int(id)][callbackNameId] << endl;
	if (writeMap[int(id)][callbackNameId] == 0) return throwError(), 0;
	if (overflowMemory(id, index)) return throwError(), 0;
	// if (int(id) >= 4000 && int(id) < 4100) {
	// 	generalMemory[int(id) + 100][int(index) + memorySize[int(id)] * entityId[gettid()]] = value;
	// 	return value;
	// }
	generalMemory[int(id)][int(index)] = value;
	return value;
}

#endif
