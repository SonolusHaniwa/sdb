vector<string> explode(string seperator, string source) {
	string src = source; vector<string> res;
	while (src.find(seperator) != string::npos) {
		int wh = src.find(seperator);
		res.push_back(src.substr(0, src.find(seperator)));
		src = src.substr(wh + string(seperator).size());
	} res.push_back(src);
	return res;
}

void commandLine() {
    if (enable_command == false) {
        shouldStop = false;
        forceStop = false;
        return;
    }
    string hint = "(sdb entity #" + to_string(currEntityId) + ") ";
    // string command = ""; getline(cin, command);
    string command = readline(hint.c_str());
    add_history(command.c_str());
    vector<string> tmp = explode(" ", command), c;
    for (int i = 0; i < tmp.size(); i++) {
        string e = tmp[i];
        while (e.size() && (e.back() == ' ' || e.back() == '\r' || e.back() == '\t' || e.back() == '\n')) e.pop_back();
        while (e.size() && (e.front() == ' ' || e.front() == '\r' || e.front() == '\t' || e.front() == '\n')) e = e.substr(1);
        if (e != "") c.push_back(e);
    }
    if (c.size() == 0) return;
    if (c[0] == "c" || c[0] == "continue") {
        shouldStop = false;
        forceStop = false;
    } 
    else if (c[0] == "q" || c[0] == "quit" || c[0] == "exit") {
        targetActiveCount = 0;
        shouldStop = false; forceStop = false;
        exit(0);
    }
    else if (c[0] == "show") {
        if (c.size() < 2) {
            cout << "Usage: show [blockId]" << endl;
            return;
        }
        int blockId = atoi(c[1].c_str());
        int offset = 0, size = memorySize[blockId];
        if (blockId >= 4000 && blockId < 4100) blockId += 100, size = memorySize[blockId] / entityCount, offset = currEntityId * size;
        for (int i = offset; i < offset + size; i += 8) {
            for (int j = i; j < i + 8 && j < offset + size; j++) cout << "#" << j - offset << "\t" << scientific << setprecision(3) << generalMemory[blockId][j] << "\t";
            cout << endl;
        }
    }
    else if (c[0] == "switch") {
        if (c.size() < 2) {
            cout << "Usage: switch [entityId]" << endl;
            return;
        }
        currEntityId = atoi(c[1].c_str());
    }
    else if (c[0] == "get") {
        if (c.size() < 3) {
            cout << "Usage: get [blockId] [offset]" << endl;
            return;
        }
        int blockId = atoi(c[1].c_str());
        int offset = atoi(c[2].c_str());
        int originalBlockId = blockId, originalOffset = offset;
        if (blockId >= 4000 && blockId < 4100) blockId += 100, offset += currEntityId * memorySize[blockId] / entityCount;
        if (overflowMemory(blockId, offset)) {
            cout << "Runtime Error: Memory Overflow!" << endl;
            return;
        }
        cout << "Memory[" << originalBlockId << "][" << originalOffset << "] = " << directGet(blockId, offset) << endl;
    }
    else if (c[0] == "set") {
        if (c.size() < 4) {
            cout << "Usage: set [blockId] [offset] [value]" << endl;
            return;
        }
        int blockId = atoi(c[1].c_str());
        int offset = atoi(c[2].c_str());
        double value = atof(c[3].c_str());
        if (blockId >= 4000 && blockId < 4100) blockId += 100, offset += currEntityId * memorySize[blockId] / entityCount;
        if (overflowMemory(blockId, offset)) {
            cout << "Runtime Error: Memory Overflow!" << endl;
            return;
        }
        directSet(blockId, offset, value);
    }
    else if (c[0] == "info") {
        cout << "Sonolus Debugger(sdb). Entity id = " << currEntityId 
             << ", archetype = \"" << levelData["entities"][currEntityId]["archetype"].asString() << "\"." << endl;
    }
    else if (c[0] == "showActive") {
        cout << "Sonolus Debugger(sdb)." << endl;
        cout << endl;
        int id = 0;
        for (auto v : activeEntities) {
            string name = "Spawned Archetype";
            if (v < levelData["entities"].size())
                name = levelData["entities"][v]["archetype"].asString();
            if (c.size() >= 2 && name.find(c[1]) == string::npos) continue;
            cout << "#" << id++ << "\tEntity id = " << v << ", archetype = \"" << name << "\"." << endl;
        }
    }
    else if (c[0] == "showQueue") {
        cout << "Sonolus Debugger(sdb)." << endl;
        cout << endl;
        int l = activePointer - 10, r = activePointer + 9;
        if (c.size() >= 2) l = activePointer + atoi(c[1].c_str());
        if (c.size() >= 3) r = activePointer + atoi(c[2].c_str());
        for (int i = max(l, 0); i < spawnOrder.size() && i <= r; i++) {
            cout << (i < activePointer ? "-" : "+") << "#" << i << "\tEntity id = " << spawnQueue[i]
                 << ", archetype = \"" << levelData["entities"][spawnQueue[i]]["archetype"].asString() 
                 << "\", spawn order = " << spawnOrder[spawnQueue[i]] << endl;
        }
    }
    else if (c[0] == "showCode") {
        if (c.size() < 2) {
            cout << "Usage: showCode [codeId] <deep = 2>" << endl;
            return;
        }
        int codeId = atoi(c[1].c_str());
        int deep = c.size() >= 3 ? atoi(c[2].c_str()) : 2;
        if (codeId >= engineData["nodes"].size()) cout << "" << endl;
        else cout << toString(codeId, 0, deep) << endl;
    }
    else if (c[0] == "b" || c[0] == "breakpoint") {
        if (c[1] == "code") {
            if (c.size() < 4 || c[2] != "add" && c[2] != "del") {
                cout << "Usage: breakpoint code [add/del] [codeId]" << endl;
                return;
            }
            if (c[2] == "add") breakpoints.insert(stoi(c[3]));
            else if (c[2] == "del") breakpoints.erase(stoi(c[3]));
        } else if (c[1] == "memory") {
            if (c.size() < 5 || c[2] != "add" && c[2] != "del") {
                cout << "Usage: breakpoint memory [add/del] [blockId] [offset]" << endl;
                return;
            }
            if (c[2] == "add") hooks.insert({ stoi(c[3]), stoi(c[4]) });
            else if (c[2] == "del") hooks.erase({ stoi(c[3]), stoi(c[4]) });
        } else if (c[1] == "function") {
            if (c.size() < 4 || c[2] != "add" && c[2] != "del") {
                cout << "Usage: breakpoint function [add/del] [func]" << endl;
                return;
            }
            if (c[2] == "add") bkfuncs.insert(c[3]);
            else if (c[2] == "del") bkfuncs.erase(c[3]);
        } else {
            cout << "Usage: breakpoint code [add/del] [codeId]" << endl;
            cout << "Usage: breakpoint memory [add/del] [blockId] [offset]" << endl;
            cout << "Usage: breakpoint function [add/del] [func]" << endl;
        }
    }
    else if (c[0] == "skip") {
        if (c.size() < 2) {
            cout << "Usage: skip <time>" << endl;
            return;
        }
        needSkip = true;
        skipTime = stod(c[1]);
        shouldStop = false;
    }
    else {
        cout << "Unknown command." << endl;
    }
}