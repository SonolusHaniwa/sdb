#ifndef Functions_StreamGetNextKey_H
#define Functions_StreamGetNextKey_H

double StreamGetNextKey(double id, double key) {
	if (streamDataKey.find(id) == streamDataKey.end()) return key;
	auto it = streamDataKey[id].upper_bound(key);
	return (it == streamDataKey[id].end() ? key : *it);
}

#endif

