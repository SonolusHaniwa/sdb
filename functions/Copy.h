#ifndef Functions_Copy_H
#define Functions_Copy_H

double Copy(double srcId, double srcIndex, double dstId, double dstIndex, double count) {
	int srcStartIndex = srcIndex;
	int dstStartIndex = dstIndex;
	int srcEndIndex = srcStartIndex + count;
	int dstEndIndex = dstStartIndex + count;
	if (int(count) < 0) return throwError("Copy length %d is less than 0!", count), 0;
	if (overflowMemory(srcId, srcStartIndex)) return throwError("Source start index %d is overflow for block %d", srcStartIndex, int(srcId)), 0;
	if (overflowMemory(srcId, srcEndIndex - 1)) return throwError("Source end index %d is overflow for block %d", srcEndIndex - 1, int(srcId)), 0;
	if (overflowMemory(dstId, dstStartIndex)) return throwError("Destination start index %d is overflow for block %d", dstStartIndex, int(dstId)), 0;
	if (overflowMemory(dstId, dstEndIndex - 1)) return throwError("Destination end index %d is overflow for block %d", dstEndIndex - 1, int(dstId)), 0;
	memmove(generalMemory[int(dstId)] + dstStartIndex, generalMemory[int(srcId)] + srcStartIndex, int(count) * sizeof(double));
	return 0;
}

#endif
