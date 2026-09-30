void throwError() {

}

int gettid() {
    int res = pthread_self() % 10000;
    return res;
    // return res < 0 || res > 10000 ? 0721 : res;
    // return syscall(__NR_gettid);
}

int archetypeCount = 0;
int entityCount = 0;
int optionCount = 0;
int bucketCount = 0;
int currEntityId;

void setEnv(int aCount, int eCount, int oCount, int bCount) {
    archetypeCount = aCount;
    entityCount = eCount;
    optionCount = oCount;
    bucketCount = bCount;
}
#include "engine/nodes.h"
#include "engine/memory.h"
#include "blocks/Play.h"
#include "blocks/Tutorial.h"
#include "blocks/Watch.h"

string mode = "";

void setMode(string mode) {
    ::mode = mode;
    for (int i = 0; i <= 10000; i++) if (memorySize[i]) destroyMemory(i);
    if (mode == "play") {
        setReadMap(readMapPlay);
        setWriteMap(writeMapPlay);
        initPlayMemory();
    } else if (mode == "tutorial") {
        setReadMap(readMapTutorial);
        setWriteMap(writeMapTutorial);
        initTutorialMemory();
    } else if (mode == "watch") {
        setReadMap(readMapWatch);
        setWriteMap(writeMapWatch);
        initWatchMemory();
    }
}

string callbackName = "";
int callbackNameId = 0;
void setCallbackName(string name) {
    callbackName = name;
    callbackNameId = callbackId.count(name) ? callbackId[name] : 99;
}

vector<int> callStacks;
#include"functions/.Functions.Extra.h"
#include"functions/.Functions.List.h"

// void optimizeNodes(set<int> immutableBlockId) {
//     // Block Access Optimization
//     for (int i = 0; i < engineData["nodes"].size(); i++) {
//         if (nodes[i].isValue) continue;
//         if (nodes[i].name != "Get" && nodes[i].name != "Set") continue;
//         if (nodes[nodes[i].param[0]].isValue == false) continue;
//         int index = nodes[nodes[i].param[0]].value;
//         if (immutableBlockId.count(index)) {
//             if (nodes[i].name == "Get" && nodes[nodes[i].param[1]].isValue) {
//                 if (overflowMemory(index, nodes[nodes[i].param[1]].value)) continue;
//                 nodes[i].value = directGet(index, nodes[nodes[i].param[1]].value);
//                 nodes[i].isValue = true;
//                 // cout << i << " Optimized! Get(" << index << ", " << nodes[nodes[i].param[1]].value << ") => " << nodes[i].value << endl;
//             } else {
//                 // cout << i << " Optimized! Set " << index << " *" << endl;
//                 nodes[i] = nodes[nodes[i].param[2]];
//             }
//         }
//     }

//     // Mathematical Optimization
//     for (int i = 0; i < engineData["nodes"].size(); i++) {
//         if (nodes[i].isValue) continue;
//         if (
//             nodes[i].name.substr(0, 4) != "Ease" &&
//             set<string>({
//                 "Add", "And", "Multiply"
//             }).count(nodes[i].name) == 0
//         ) continue;
//         vector<int> tmp;
//         for (int j = 0; j < nodes[i].param.size(); j++) {
//             int nodeId = nodes[i].param[j];
//             if (nodes[nodeId].isValue == false && nodes[nodeId].name == nodes[i].name)
//                 for (int k = 0; k < nodes[nodeId].param.size(); k++) tmp.push_back(nodes[nodeId].param[k]);
//             else tmp.push_back(nodeId);
//         }
//         nodes[i].param = tmp;
//         nodes[i].values.resize(nodes[i].param.size());
//     }
//     for (int i = 0; i < engineData["nodes"].size(); i++) {
//         if (nodes[i].isValue) continue;
//         if (
//             nodes[i].name.substr(0, 4) != "Ease" &&
//             set<string>({
//                 "Abs", "Add", "And", "Arccos", "Arcsin", "Arctan", "Arctan2",
//                 "Ceil", "Clamp", "Cos", "Cosh", 
//                 "Degree", "Divide",
//                 "Equal", "Floor", "Frac", "Greater", "GreaterOr",
//                 "Lerp", "LerpClamped", "Less", "LessOr", "Log", "Max", "Min", "Mod",
//                 "Multiply", "Negate", "Not", "NotEqual", "Or", "Power", "Radian", "Rem", "Remap", "RemapClamped",
//                 "Round", "Sign", "Sin", "Sinh", "Subtract", "Tan", "Tanh", "Trunc", "Unlerp", "UnlerpClamped"
//             }).count(nodes[i].name) == 0
//         ) continue;
//         bool isValue = true;
//         for (int j = 0; j < nodes[i].param.size(); j++) isValue &= nodes[nodes[i].param[j]].isValue;
//         if (isValue) {
//             double value = RunCode(i);
//             nodes[i].isValue = true;
//             nodes[i].value = value;
//         }
//     }
//     for (int i = 0; i < engineData["nodes"].size(); i++) {
//         if (nodes[i].isValue) continue;
//         if (
//             nodes[i].name.substr(0, 4) != "Ease" &&
//             set<string>({
//                 "Abs", "Add", "And", "Arccos", "Arcsin", "Arctan", "Arctan2",
//                 "Ceil", "Clamp", "Cos", "Cosh", 
//                 "Degree", "Divide",
//                 "Equal", "Floor", "Frac", "Greater", "GreaterOr",
//                 "Lerp", "LerpClamped", "Less", "LessOr", "Log", "Max", "Min", "Mod",
//                 "Multiply", "Negate", "Not", "NotEqual", "Or", "Power", "Radian", "Rem", "Remap", "RemapClamped",
//                 "Round", "Sign", "Sin", "Sinh", "Subtract", "Tan", "Tanh", "Trunc", "Unlerp", "UnlerpClamped"
//             }).count(nodes[i].name) == 0
//         ) continue;
//         bool isValue = true;
//         for (int j = 0; j < nodes[i].param.size(); j++) isValue &= nodes[nodes[i].param[j]].isValue;
//         if (isValue) {
//             double value = RunCode(i);
//             nodes[i].isValue = true;
//             nodes[i].value = value;
//         }
//     }

//     // Control Flow Optimization
//     for (int i = 0; i < engineData["nodes"].size(); i++) {
//         if (nodes[i].isValue) continue;
//         if (nodes[i].name == "If" && nodes[nodes[i].param[0]].isValue) {
//             nodes[i] = nodes[nodes[i].param[0]].value ? nodes[nodes[i].param[1]] : nodes[nodes[i].param[2]];
//         }
//         if (nodes[i].name == "While" && nodes[nodes[i].param[0]].isValue && nodes[nodes[i].param[0]].value == false) {
//             nodes[i].isValue = true;
//             nodes[i].value = 0;
//         }
//         if (nodes[i].name == "Execute0" && nodes[i].param.size() == 1) {
//             nodes[i] = nodes[nodes[i].param[0]];
//         }
//         if (nodes[i].name == "Execute" && nodes[i].param.size() == 1) {
//             nodes[i] = nodes[nodes[i].param[0]];
//         }
//     }
// }

vector<DrawElement> renderDrawLists;
#include "engine/play.h"
#include "engine/tutorial.h"
#include "engine/watch.h"

// Unknown Function: Stack*x16
// Outside Function: DebugLog DebugPause DestroyParticleEffect Draw*x7 ExportValue Has*x3 MoveParticleEffect Paint Play*x4 Print Spawn SpawnParticleEffect