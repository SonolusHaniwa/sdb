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
    if (c[0] == "c") {
        shouldStop = false;
        forceStop = false;
    } 
    else if (c[0] == "q") {
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
            for (int j = i; j < i + 8 && j < offset + size; j++) cout << "#" << j - offset << "\t" << generalMemory[blockId][j] << "\t";
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
    // else if (c[0] == "draw") {
    //     // draw ../../sonolus-server-cpp/phigros/dist/SkinData ../../sonolus-server-cpp/phigros/dist/SkinTexture test.png
    //     if (c.size() < 4) {
    //         cout << "Usage: draw  [path]" << endl;
    //         return;
    //     }
    //     Json::Value skinData = json_decode(decompress_gzip(readFile(c[1])));
    //     image skinTexture = readImage(c[2]);
    //     mkdir(".tmp", 0777);
    //     map<int, string> spriteName;
    //     map<string, int> realSpriteId;
    //     for (int i = 0; i < engineData["skin"]["sprites"].size(); i++)
    //         spriteName[engineData["skin"]["sprites"][i]["id"].asInt()] = engineData["skin"]["sprites"][i]["name"].asString();
    //     for (int i = 0; i < skinData["sprites"].size(); i++)
    //         realSpriteId[skinData["sprites"][i]["name"].asString()] = i;
    //     string savePath = c[3];
    //     string command = "convert -size " + to_string(width * 3) + "x" + to_string(height * 3) + " ";
    //     sort(drawLists.begin(), drawLists.end(), [](DrawElement a, DrawElement b){ return a.z < b.z; });
    //     for (int i = 0; i < drawLists.size(); i++) {
    //         if (
    //             drawLists[i].x1 < -width || drawLists[i].y1 < -height || drawLists[i].x1 > width * 2 || drawLists[i].y1 > height * 2 ||
    //             drawLists[i].x2 < -width || drawLists[i].y2 < -height || drawLists[i].x2 > width * 2 || drawLists[i].y2 > height * 2 ||
    //             drawLists[i].x3 < -width || drawLists[i].y3 < -height || drawLists[i].x3 > width * 2 || drawLists[i].y3 > height * 2 ||
    //             drawLists[i].x4 < -width || drawLists[i].y4 < -height || drawLists[i].x4 > width * 2 || drawLists[i].y4 > height * 2
    //         ) continue;
    //         // cout << spriteName[drawLists[i].spriteId] << " " 
    //         //      << drawLists[i].x1 << ", " << drawLists[i].y1 << " "
    //         //      << drawLists[i].x2 << ", " << drawLists[i].y2 << " "
    //         //      << drawLists[i].x3 << ", " << drawLists[i].y3 << " "
    //         //      << drawLists[i].x4 << ", " << drawLists[i].y4 << " "
    //         //      << drawLists[i].a << endl;
    //         // continue;
    //         Json::Value data = skinData["sprites"][realSpriteId[spriteName[drawLists[i].spriteId]]];
    //         image sprite = image(data["w"].asInt(), data["h"].asInt());
    //         for (int x = data["x"].asInt(), x0 = 0; x < data["x"].asInt() + data["w"].asInt(); x++, x0++) {
    //             for (int y = data["y"].asInt(), y0 = 0; y < data["y"].asInt() + data["h"].asInt(); y++, y0++) {
    //                 sprite.data[y0][x0 * 4] = skinTexture.data[y][x * 4];
    //                 sprite.data[y0][x0 * 4 + 1] = skinTexture.data[y][x * 4 + 1];
    //                 sprite.data[y0][x0 * 4 + 2] = skinTexture.data[y][x * 4 + 2];
    //                 sprite.data[y0][x0 * 4 + 3] = skinTexture.data[y][x * 4 + 3] * drawLists[i].a;
    //                 // if (drawLists[i].a == 0.8) cout << int(skinTexture.data[y][x * 4 + 3]) << " " << skinTexture.data[y][x * 4 + 3] * drawLists[i].a << endl;
    //             }
    //         }
    //         drawLists[i].x1 += width; drawLists[i].y1 += height;
    //         drawLists[i].x2 += width; drawLists[i].y2 += height;
    //         drawLists[i].x3 += width; drawLists[i].y3 += height;
    //         drawLists[i].x4 += width; drawLists[i].y4 += height;
    //         writeImage(".tmp/" + to_string(i) + ".png", sprite);
    //         int w = data["w"].asInt(), h = data["h"].asInt();
    //         command += "\\( \"./.tmp/" + to_string(i) + ".png\" -filter point -virtual-pixel none +distort perspective \"";
    //         command += "0," + to_string(h == 1 ? h : h - 1) + " " + to_string(drawLists[i].x1) + "," + to_string(height - drawLists[i].y1) + " ";
    //         command += "0,0 " + to_string(drawLists[i].x2) + "," + to_string(height - drawLists[i].y2) + " ";
    //         command += to_string(w == 1 ? w : w - 1) + ",0" + " " + to_string(drawLists[i].x3) + "," + to_string(height - drawLists[i].y3) + " ";
    //         command += to_string(w == 1 ? w : w - 1) + "," + to_string(h == 1 ? h : h - 1) + " " + to_string(drawLists[i].x4) + "," + to_string(height - drawLists[i].y4);
    //         command += "\" \\) ";
    //     }
    //     command += "-background none -layers merge \"" + savePath + "\"";
    //     system(command.c_str());
    //     // string command = "convert bag.png \( G.png -virtual-pixel none +distort perspective "0,0 75,280  116,0 155,311  116,119 141,367  0,119 64,329" \) -layers flatten +repage result.png"
    // }
    else if (c[0] == "breakpoint") {
        
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