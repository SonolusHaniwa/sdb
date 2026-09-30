#ifndef Functions_StreamGetValue_H
#define Functions_StreamGetValue_H

double StreamGetValue(double id, double key) {
	if (streamDataKey.find(id) == streamDataKey.end()) return 0;
	auto it = streamDataKey[id].lower_bound(key);
	if (it == streamDataKey[id].begin()) return streamDataValue[id][*it];
	if (it == streamDataKey[id].end()) return streamDataValue[id][*--it];
	return RemapClamped(*--it, *it, streamDataValue[id][*--it], streamDataValue[id][*it], key);
}

#endif

