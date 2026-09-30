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
    double z, a;
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

// All Functions
int cnt = 0;
map<string, int> ExecuteTimes;

void beforeRunCode(int nodeId) {
    cnt++;
	if (forceStop) {
		cout << endl;
		cout << "Stucked in entity #" << entityId << "(archetype = \"" << archetypeName << "\", callback = \"" << callbackName << "\")" << endl;
		for (int i = callStacks.size() - 1; i >= 0; i--) {
			DataNode node = nodes[callStacks[i]];
			string callName = node.callName;
			for (int j = 0; j < node.currValueCount; j++) callName = callName.replace(callName.find("?"), 1, to_string(node.values[j]));
			cout << "#" << (callStacks.size() - 1 - i) << "\t" << callName << endl;
		}
    	currEntityId = entityId;
        while (forceStop) commandLine();
	}
    if (!nodes[nodeId].isValue) callStacks.push_back(nodeId);
}

void afterRunCode(int nodeId) {
    callStacks.pop_back();
    ExecuteTimes[nodes[nodeId].name]++;
}