class DataNode {
    public:

    bool isValue = true;
    double value = 0;
    string name = "";
    vector<int> param = {};

    string id = "";
    string callName = "";
    vector<double> values = {};
    int currValueCount = 0;
    int hash = 0;
    int currParam = 0;
};

int calcHash(string s) {
    int64_t res = 0;
    for (int i = 0; i < s.size(); i++) res *= 55331, res += s[i], res %= 998244353;
    return res;
}

DataNode* nodes;

void initNodes(Json::Value nodes) {
    ::nodes = new DataNode[nodes.size()];
    for (int i = 0; i < nodes.size(); i++) {
        DataNode newNode;
        newNode.id = to_string(i);
        while (newNode.id.size() < 8) newNode.id = "0" + newNode.id;
        if (nodes[i].isMember("value")) {
            newNode.isValue = true;
            newNode.value = nodes[i]["value"].asDouble();
        } else {
            newNode.isValue = false;
            newNode.name = nodes[i]["func"].asString();
            for (int j = 0; j < nodes[i]["args"].size(); j++) 
                newNode.param.push_back(nodes[i]["args"][j].asInt()),
                newNode.values.push_back(0);
        }
        if (newNode.isValue == false) {
            newNode.callName = newNode.id + " in " + newNode.name + "(";
            for (int j = 0; j < newNode.param.size(); j++) newNode.callName += (j ? ", ?" : "?");
            newNode.callName += ")";
            newNode.hash = calcHash(newNode.name);
        }
        (::nodes[i]) = newNode;
    }
}

string toString(int nodeId, int tabLength = 0, int deep = 2, int paramOff = 0, int paramLim = 16) {
    stringstream ss; string pre = "";
    for (int i = 0; i < tabLength; i++) pre += "  ";
    DataNode node = nodes[nodeId];
    if (node.isValue) return ss << pre << node.value, ss.str();
    bool allValue = true;
    for (int i = 0; i < node.param.size(); i++) allValue &= nodes[node.param[i]].isValue;
    if (allValue) {
        ss << pre << node.name << "(";
        if (paramOff) ss << "...and " << min(paramOff, int(node.param.size())) << " params" << (paramOff < node.param.size() ? ", " : "");
        for (int i = paramOff; i < min(int(node.param.size()), paramOff + paramLim); i++) 
            ss << nodes[node.param[i]].value << (i != node.param.size() - 1 ? ", " : "");
        if (node.param.size() > paramOff + paramLim) ss << "...and " << node.param.size() - (paramOff + paramLim) << " params";
        ss << ")";
    } else {
        ss << pre << node.name << "(";
        if (tabLength < deep - 1) ss << endl;
        if (paramOff) {
            if (tabLength < deep - 1) ss << pre << "  ...and " << min(paramOff, int(node.param.size())) << " params" << (paramOff < node.param.size() ? "," : "") << endl;
            else ss << "...and " << min(paramOff, int(node.param.size())) << " params" << (paramOff < node.param.size() ? ", " : "");
        }
        for (int i = paramOff; i < min(int(node.param.size()), paramOff + paramLim); i++) {
            if (tabLength >= deep - 1) {
                if (nodes[node.param[i]].isValue) ss << nodes[node.param[i]].value;
                else ss << "...";
                ss << (i != node.param.size() - 1 ? ", " : "");
            } else ss << toString(node.param[i], tabLength + 1, deep) << (i != node.param.size() - 1 ? "," : "") << " \033[32m# codeId = " << node.param[i] << "\033[0m, \033[33mparamId = " << i << "\033[0m" << endl;
        }
        if (node.param.size() > paramOff + paramLim) {
            if (tabLength < deep - 1) ss << pre << "  ...and " << node.param.size() - (paramOff + paramLim) << " params" << endl;
            else ss << "...and " << node.param.size() - (paramOff + paramLim) << " params";
        }
        if (tabLength < deep - 1) ss << pre;
        ss << ")";
    }
    return ss.str();
}