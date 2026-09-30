/**
 * @author 2024 (c) LittleYang0531
 * @date 2024/12/15
 */

#include<bits/stdc++.h>
using namespace std;
#include"../include/json.h"

int getSize(Json::Value p) {
    if (p["type"] == "group") {
        int num = 0;
        for (int i = 0; i < p["items"].size(); i++) num += getSize(p["items"][i]);
        if (p.isMember("minCount")) return -num;
        else if (p.isMember("count")) return num * p["count"].asInt();
        else if (p.isMember("forEach")) return num * p["forEach"].size();
        return num;
    } else {
        if (p.isMember("minCount")) return -1;
        else if (p.isMember("count")) return p["count"].asInt();
        else if (p.isMember("forEach")) return p["forEach"].size();
        return 1;
    }
}

int main(int argc, char** argv) {
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " Blocks.json Blocks.h mode" << endl;
        return 1;
    }
    ifstream fin; fin.open(argv[1]);
    fin.seekg(0, ios::end);
    int len = fin.tellg();
    char *ch = new char[len];
    fin.seekg(0, ios::beg);
    fin.read(ch, len);
    string s = string(ch, len);
    Json::Value json = json_decode(s);
    fin.close();
    ofstream fout; fout.open(argv[2]);
    string id = argv[3];
    int h = 0; for (int i = 0; i < id.size(); i++) h += id[i];
    srand(h);
    fout << "#ifndef " << argv[3] << "Blocks_H" << endl;
    fout << "#define " << argv[3] << "Blocks_H" << endl;
    fout << endl;
    fout << "map<int, set<string> > readMap" << argv[3] << " = {" << endl;
    for (int i = 0; i < json.size(); i++) {
        fout << "\t{ " << json[i]["id"].asString() << ", { ";
        for (int j = 0; j < json[i]["readable"].size(); j++) 
            fout << "\"" << json[i]["readable"][j].asString() << "\"" << (j != json[i]["readable"].size() - 1 ? ", " : "");
        fout << " } }" << (i != json.size() - 1 ? "," : "") << endl;
    }
    fout << "};" << endl;
    fout << "map<int, set<string> > writeMap" << argv[3] << " = {" << endl;
    for (int i = 0; i < json.size(); i++) {
        fout << "\t{ " << json[i]["id"].asString() << ", { ";
        for (int j = 0; j < json[i]["writable"].size(); j++) 
            fout << "\"" << json[i]["writable"][j].asString() << "\"" << (j != json[i]["writable"].size() - 1 ? ", " : "");
        fout << " } }" << (i != json.size() - 1 ? "," : "") << endl;
    }
    fout << "};" << endl;
    fout << "void init" << argv[3] << "Memory() {" << endl;
    for (int i = 0; i < json.size(); i++) {
        fout << "\tsetMemory(" << json[i]["id"].asString() << ", ";
        int num = 0; string extra = "";
        for (int j = 0; j < json[i]["values"].size(); j++) num += getSize(json[i]["values"][j]);
        if (num < 0) {
            if (json[i]["name"].asString().find("Archetype") != string::npos) num = -num, extra = " * archetypeCount";
            else if (json[i]["name"].asString().find("Entity") != string::npos) num = -num, extra = " * entityCount";
            else if (json[i]["name"].asString().find("Option") != string::npos) num = -num, extra = " * optionCount";
            else if (json[i]["name"].asString().find("Bucket") != string::npos) num = -num, extra = " * bucketCount";
            else num = 0;
        }
        fout << num << extra << ");" << endl;
    }
    fout << "}" << endl;
    fout << endl;
    fout << "#endif" << endl;
    fout.close();
}