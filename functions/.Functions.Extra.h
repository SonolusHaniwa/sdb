// BPM Function
class BPM {
    public:

    double startBeat, startTime;
    double bpm;
};
vector<BPM> bpmList = { { 0, 0, 60 } };

// Easing Function
const double PI = acos(-1);
const double c1 = 1.70158;
const double c3 = c1 + 1;
const double c4 = (2 * PI) / 3;

// Random Function
bool initializeRandomFunction = [](){ srand(time(NULL)); return true; };

// TimeScale Function
class TimeScale {
    public:

    double startTime, startScaledTime;
    double scaledValue;
};
vector<TimeScale> timeScaleList = { { 0, 0, 1 } };

// Control Flow Function
int breakCount = 0; double breakValue = 0;

// Stream Function
map<int, set<double> > streamDataKey;
map<int, map<double, double> > streamDataValue;

// Draw Function
class DrawElement {
    public:

    int spriteId;
    double x1, y1;
    double x2, y2;
    double x3, y3;
    double x4, y4;
    double z1, z2, z3, z4, a;
};
int RuntimeSkinTransformId;
vector<DrawElement> drawLists;

// ParticleFunction
int RuntimeParticleTransformId;
map<int, ParticleDataEffect> activeEffects;
int particleCount = 0;

// Debug Function
int entityId;
string archetypeName;
double currTime;
// map<int, int> entityId;
// map<int, string> archetypeName;
// map<int, double> currTime;

// Spawn Function
function<void(double, vector<double>)> customSpawn = [](double id, vector<double> memory) {
	cerr << "\e[31mCalled not implemented function \"Spawn(";
	cerr << "id: " << id;
	cerr << ", memory: " << "{ "; for (int i = 0; i < memory.size(); i++) cerr << (i ? ", " : "") << "[" << i << "] = " << memory[i]; cerr << " }";
	cerr << ")\"!\e[0m" << endl;
};

// Stack Function
int TemporaryMemoryId = 10000;
int TemporaryMemorySize = 4096;

// All Functions
int cnt = 0;
map<string, int> ExecuteTimes;

void beforeRunCode(int nodeId) {
    if (!nodes[nodeId].isValue) callStacks.push_back(nodeId);
    if (breakpoints.count(nodeId)) {
        cout << endl;
        cout << "Breakpoint on code " << nodeId << " was triggered.";
        forceStop = true;
    }
    // if (nodes[nodeId].name == "Set") {
    //     cout << int(nodes[nodeId].values[1]) << " " << int(nodes[nodeId].values[2]) << " " << hooks.count({ int(nodes[nodeId].values[1]), int(nodes[nodeId].values[2]) }) << endl;
    // }
    cnt++;
	if (forceStop) {
		cout << endl;
		cout << "Stucked in entity #" << entityId << "(archetype = \"" << archetypeName << "\", callback = \"" << callbackName << "\")" << endl;
		for (int i = callStacks.size() - 1, k = 0; i >= 0 && k < 16; i--, k++) {
			DataNode node = nodes[callStacks[i]];
			string callName = node.callName;
			for (int j = 0; j < node.currValueCount; j++) callName = callName.replace(callName.find("?"), 1, to_string(node.values[j]));
			cout << "#" << (callStacks.size() - 1 - i) << "\t" << callName << endl;
		}
        if (callStacks.size() > 16) cout << "..." << endl;
    	currEntityId = entityId;
        while (forceStop) commandLine();
	}
}

void beforeRunMainCode(int nodeId) {
    if (nodes[nodeId].name == "Set" && hooks.count({ int(nodes[nodeId].values[0]), int(nodes[nodeId].values[1]) })) {
        cout << endl;
        cout << "Breakpoint on blockId = " << int(nodes[nodeId].values[0]) << ", offset = " << int(nodes[nodeId].values[1]) << " was triggered.";
        forceStop = true;
    }
    if (bkfuncs.count(nodes[nodeId].name)) {
        cout << endl;
        cout << "Breakpoint on func \"" << nodes[nodeId].name << "\" was triggered.";
        forceStop = true;
    }
	if (forceStop) {
		cout << endl;
		cout << "Stucked in entity #" << entityId << "(archetype = \"" << archetypeName << "\", callback = \"" << callbackName << "\")" << endl;
		for (int i = callStacks.size() - 1, k = 0; i >= 0 && k < 16; i--, k++) {
			DataNode node = nodes[callStacks[i]];
			string callName = node.callName;
			for (int j = 0; j < node.currValueCount; j++) callName = callName.replace(callName.find("?"), 1, to_string(node.values[j]));
			cout << "#" << (callStacks.size() - 1 - i) << "\t" << callName << endl;
		}
        if (callStacks.size() > 16) cout << "..." << endl;
    	currEntityId = entityId;
        while (forceStop) commandLine();
	}
}

void afterRunCode(int nodeId) {
    callStacks.pop_back();
    ExecuteTimes[nodes[nodeId].name]++;
}