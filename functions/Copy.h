#ifndef Functions_Copy_H
#define Functions_Copy_H

double Copy(double srcId, double srcIndex, double dstId, double dstIndex, double count) {
	int srcStartIndex = srcIndex;
	int dstStartIndex = dstIndex;
	int srcEndIndex = srcStartIndex + count;
	int dstEndIndex = dstStartIndex + count;
	if (int(count) < 0) return throwError(), 0;
	if (overflowMemory(srcId, srcStartIndex)) return throwError(), 0;
	if (overflowMemory(srcId, srcEndIndex - 1)) return throwError(), 0;
	if (overflowMemory(dstId, dstStartIndex)) return throwError(), 0;
	if (overflowMemory(dstId, dstEndIndex - 1)) return throwError(), 0;
	memmove(generalMemory[int(dstId)] + dstStartIndex, generalMemory[int(srcId)] + srcStartIndex, int(count));
	return 0;
}

#endif
