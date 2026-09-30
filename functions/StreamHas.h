#ifndef Functions_StreamHas_H
#define Functions_StreamHas_H

double StreamHas(double id, double key) {
	if (streamDataKey.find(id) == streamDataKey.end()) return false;
	return streamDataKey[id].count(key);
}

#endif

