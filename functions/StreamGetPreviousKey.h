#ifndef Functions_StreamGetPreviousKey_H
#define Functions_StreamGetPreviousKey_H

double StreamGetPreviousKey(double id, double key) {
	if (streamDataKey.find(id) == streamDataKey.end()) return key;
	auto it = streamDataKey[id].lower_bound(key);
	return (it == streamDataKey[id].begin() ? key : *--it);
}

#endif

