#ifndef Functions_StreamSet_H
#define Functions_StreamSet_H

double StreamSet(double id, double key, double value) {
	streamDataKey[id].insert(key);
	streamDataValue[id][key] = value;
	return 0;
}

#endif

