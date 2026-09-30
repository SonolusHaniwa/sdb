double* generalMemory[10001];
int memorySize[10001];
bool isLinked[10001];
bool readMap[10001][101], writeMap[10001][101];
map<string, int> callbackId;

bool overflowMemory(int id, int index) {
    return id < 0 || id > 10000 || index < 0 || index >= memorySize[id];
}

void setMemory(int id, int size) {
    if (size == 0) return;
    assert(memorySize[id] == 0);
    memorySize[id] = size;
    generalMemory[id] = new double[size];
    memset(generalMemory[id], 0, size);
    isLinked[id] = 0;
}

void linkMemory(int id, int size, int targetId, int offset) {
    if (size == 0) return;
    assert(memorySize[id] == 0);
    assert(!overflowMemory(targetId, offset));
    assert(!overflowMemory(targetId, offset + size - 1));
    memorySize[id] = size;
    generalMemory[id] = generalMemory[targetId] + offset;
    isLinked[id] = 1;
}

void linkMemory(int id, int size, double* target, int offset) {
    if (size == 0) return;
    assert(memorySize[id] == 0);
    memorySize[id] = size;
    generalMemory[id] = target + offset;
    isLinked[id] = 1;
}

void destroyMemory(int id) {
    if (memorySize[id] == 0) return;
    memorySize[id] = 0;
    if (!isLinked[id]) delete[] generalMemory[id];
}

int callbackIdCount = 0;
void setReadMap(map<int, set<string> > r) {
    callbackIdCount = 0; callbackId.clear();
    memset(readMap, 0, sizeof readMap);
    for (auto v : r) {
        for (auto name : v.second) {
            int blockId = v.first;
            int id = callbackId.count(name) ? callbackId[name] : callbackId[name] = callbackIdCount++;
            readMap[blockId][id] = 1;
        }
    }
}

void setWriteMap(map<int, set<string> > w) {
    memset(writeMap, 0, sizeof writeMap);
    for (auto v : w) {
        for (auto name : v.second) {
            int blockId = v.first;
            int id = callbackId.count(name) ? callbackId[name] : callbackId[name] = callbackIdCount++;
            writeMap[blockId][id] = 1;
        }
    }
}

double directGet(int id, int index) {
    assert(!overflowMemory(id, index));
    return generalMemory[id][index];
}

void directSet(int id, int index, double value) {
    assert(!overflowMemory(id, index));
    generalMemory[id][index] = value;
}