namespace play {
    const int targetFPS = 120;
    map<string, int> aids;
    map<string, map<string, pair<int, int> > > importData;
    vector<int> entityAid;
    vector<vector<int> > callbackOrder;
    vector<int> preprocessOrder, spawnOrderOrder;
    vector<int> initializeOrder, updateSequentialOrder, touchOrder, updateParallelOrder;
    vector<int> terminateOrder;

    vector<double**> newSpawnedMemory;
    
    void startEntity(int i) {
        if (i < entityCount) for (int j = 0; j < 8; j++) linkMemory(4000 + j, memorySize[4100 + j] / entityCount, 4100 + j, memorySize[4100 + j] / entityCount * i);
        else for (int j = 0; j < 8; j++) linkMemory(4000 + j, memorySize[4100 + j] / entityCount, newSpawnedMemory[i - entityCount][j], 0);
    }
    void endEntity() {
        for (int j = 0; j < 8; j++) destroyMemory(4000 + j);
    }
    bool cmp(int a, int b) {
        int aidA = entityAid[a];
        int aidB = entityAid[b];
        double orderA = callbackOrder[aidA][callbackNameId], 
                orderB = callbackOrder[aidB][callbackNameId];
        return orderA == orderB ? a < b : orderA < orderB;
    };

    vector<pair<int, vector<double> > > newSpawnList;
    function<void(double, vector<double>)> customSpawn = [](double id, vector<double> memory){
        if (id < 0 || id >= engineData["archetypes"].size()) return;
        int aid = id; 
        double** newMemory = new double*[8];
        for (int i = 0; i < 8; i++) newMemory[i] = new double[memorySize[4100 + i] / entityCount];
        newSpawnedMemory.push_back(newMemory);
        entityAid.push_back(aid);
        newSpawnList.push_back({ entityAid.size() - 1, memory });
        // cout << "New Spawn: Entity id = " << entityAid.size() - 1 << ", archetype = \"Spawned: " << engineData["archetypes"][aid]["name"].asString() << "\"" << endl;
    };

    void solveArchetypes() {
        for (int i = 0; i < engineData["archetypes"].size(); i++) {
            string name = engineData["archetypes"][i]["name"].asString();
            aids[name] = i;
            importData[name] = {};
            for (int j = 0; j < engineData["archetypes"][i]["imports"].size(); j++) {
                int index = engineData["archetypes"][i]["imports"][j]["index"].asInt();
                double def = engineData["archetypes"][i]["imports"][j]["def"].asDouble();
                string var = engineData["archetypes"][i]["imports"][j]["name"].asString();
                importData[name][var] = { index, def };
            }
        }
        callbackOrder.resize(engineData["archetypes"].size());
        for (int i = 0; i < engineData["archetypes"].size(); i++) {
            callbackOrder[i].resize(callbackIdCount);
            callbackOrder[i][callbackId["preprocess"]] = engineData["archetypes"][i].isMember("preprocess") ? engineData["archetypes"][i]["preprocess"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["spawnOrder"]] = engineData["archetypes"][i].isMember("spawnOrder") ? engineData["archetypes"][i]["spawnOrder"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["shouldSpawn"]] = engineData["archetypes"][i].isMember("shouldSpawn") ? engineData["archetypes"][i]["shouldSpawn"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["initialize"]] = engineData["archetypes"][i].isMember("initialize") ? engineData["archetypes"][i]["initialize"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["updateSequential"]] = engineData["archetypes"][i].isMember("updateSequential") ? engineData["archetypes"][i]["updateSequential"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["touch"]] = engineData["archetypes"][i].isMember("touch") ? engineData["archetypes"][i]["touch"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["updateParallel"]] = engineData["archetypes"][i].isMember("updateParallel") ? engineData["archetypes"][i]["updateParallel"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["terminate"]] = engineData["archetypes"][i].isMember("terminate") ? engineData["archetypes"][i]["terminate"]["order"].asDouble() : 0;
        }
    }

    void prepareBlocks() {
        // 重新分配内存
        setMemory(4100, 64 * entityCount);
        setMemory(4104, 1 * entityCount);
        setMemory(4105, 5 * entityCount);
        for (int i = 0; i < 8; i++) destroyMemory(4000 + i);

        // 预填数据
        directSet(1000, 0, 1);
        directSet(1000, 1, 1.0 * width / height);
        directSet(1000, 2, 0);
        directSet(1000, 3, 0);
        directSet(1000, 4, 0);
        for (int i = 0; i < 16; i++) directSet(1003, i, 0);
        directSet(1003, 0, 1);
        directSet(1003, 5, 1);
        directSet(1003, 10, 1);
        directSet(1003, 15, 1);
        for (int i = 0; i < 16; i++) directSet(1004, i, 0);
        directSet(1004, 0, 1);
        directSet(1004, 5, 1);
        directSet(1004, 10, 1);
        directSet(1004, 15, 1);
        for (int i = 0; i < 10; i++) directSet(1007, i, 1);
        for (int i = 0; i < options.size(); i++) directSet(2002, i, options[i]);
        map<string, int> refs;
        for (int i = 0; i < levelData["entities"].size(); i++)
            if (levelData["entities"][i].isMember("name")) refs[levelData["entities"][i]["name"].asString()] = i;
        entityAid.resize(levelData["entities"].size());
        for (int i = 0; i < levelData["entities"].size(); i++) {
            string aname = levelData["entities"][i]["archetype"].asString();
            // 处理特殊原型
            if (aname == "#BPM_CHANGE") {
                BPM newBPM;
                for (int j = 0; j < levelData["entities"][i]["data"].size(); j++) {
                    string name = levelData["entities"][i]["data"][j]["name"].asString();
                    double value = levelData["entities"][i]["data"][j].isMember("ref")
                        ? refs[levelData["entities"][i]["data"][j]["ref"].asString()]
                        : levelData["entities"][i]["data"][j]["value"].asDouble();
                    if (name == "#BEAT") newBPM.startBeat = value;
                    if (name == "#BPM") newBPM.bpm = value;
                }
                bpmList.push_back(newBPM);
            }
            if (aname == "#TIMESCALE_CHANGE") {
                TimeScale newTimeScale;
                for (int j = 0; j < levelData["entities"][i]["data"].size(); j++) {
                    string name = levelData["entities"][i]["data"][j]["name"].asString();
                    double value = levelData["entities"][i]["data"][j].isMember("ref")
                        ? refs[levelData["entities"][i]["data"][j]["ref"].asString()]
                        : levelData["entities"][i]["data"][j]["value"].asDouble();
                    if (name == "#BEAT") newTimeScale.startTime = value;
                    if (name == "#TIMESCALE") newTimeScale.scaledValue = value;
                }
                timeScaleList.push_back(newTimeScale);
            }
            int aid = aids.find(aname) == aids.end() ? -1 : aids[aname];
            entityAid[i] = aid;
            targetActiveCount += aid == -1 ? 0 : engineData["archetypes"][aid]["hasInput"].asBool();

            startEntity(i);
            for (int j = 0; j < 64; j++) directSet(4000, j, 0);
            for (int j = 0; j < 32; j++) directSet(4001, j, 0);
            for (int j = 0; j < 32; j++) directSet(4002, j, 0);
            if (aid != -1) {
                for (const auto &v : importData[aname]) {
                    int index = v.second.first;
                    double def = v.second.second;
                    if (overflowMemory(4001, index)) continue;
                    directSet(4001, index, def);
                }
                for (int j = 0; j < levelData["entities"][i]["data"].size(); j++) {
                    string name = levelData["entities"][i]["data"][j]["name"].asString();
                    if (importData[aname].count(name) == 0) continue;
                    double value = levelData["entities"][i]["data"][j].isMember("ref")
                        ? refs[levelData["entities"][i]["data"][j]["ref"].asString()]
                        : levelData["entities"][i]["data"][j]["value"].asDouble();
                    int index = importData[aname][name].first;
                    if (overflowMemory(4001, index)) continue;
                    directSet(4001, index, value);
                }
            }
            directSet(4003, 0, i);
            directSet(4003, 1, aid);
            directSet(4003, 2, 0);
            directSet(4004, 0, 0);
            directSet(4005, 0, 0);
            directSet(4005, 1, 0);
            directSet(4005, 2, -1);
            directSet(4005, 3, 0);
            endEntity();
        }
    }

    void solveBlocks() {
        sort(bpmList.begin(), bpmList.end(), [](BPM a, BPM b){ return a.startBeat == b.startBeat ? a.bpm < b.bpm : a.startBeat < b.startBeat; });
        for (int i = 1; i < bpmList.size(); i++) 
            bpmList[i].startTime = bpmList[i - 1].startTime + (bpmList[i].startBeat - bpmList[i - 1].startBeat) / bpmList[i].bpm * 60;
        for (int i = 1; i < timeScaleList.size(); i++) timeScaleList[i].startTime = BeatToTime(timeScaleList[i].startTime);
        sort(timeScaleList.begin(), timeScaleList.end(), [](TimeScale a, TimeScale b){ return a.startTime < b.startTime; });
        for (int i = 1; i < timeScaleList.size(); i++) 
            timeScaleList[i].startScaledTime 
                = timeScaleList[i - 1].startScaledTime 
                + (timeScaleList[i].startTime - timeScaleList[i - 1].startTime) * timeScaleList[i - 1].scaledValue;
    }

    void runPreprocess() {
        double t1 = 1.0 * clock2() / CLOCKS_PER_SEC;
        setCallbackName("preprocess");
        sort(preprocessOrder.begin(), preprocessOrder.end(), cmp);
        for (auto eid : preprocessOrder) {
            int aid = entityAid[eid];
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            RunCode(engineData["archetypes"][aid]["preprocess"]["index"].asInt());
            endEntity();
        }
        double t2 = 1.0 * clock2() / CLOCKS_PER_SEC;
        cout << "Preprocess: Use " << (t2 - t1) << "s / " << levelData["entities"].size() << " entities" << endl;
    }

    void runSpawnOrder() {
        spawnOrder.resize(levelData["entities"].size());
        double t1 = 1.0 * clock2() / CLOCKS_PER_SEC;
        setCallbackName("spawnOrder");
        sort(spawnOrderOrder.begin(), spawnOrderOrder.end(), cmp);
        for (auto eid : spawnOrderOrder) {
            int aid = entityAid[eid];
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            double order = engineData["archetypes"][aid].isMember("spawnOrder") ? RunCode(engineData["archetypes"][aid]["spawnOrder"]["index"].asInt()) : 0;
            spawnOrder[entityId] = order;
            endEntity();
        }
        double t2 = 1.0 * clock2() / CLOCKS_PER_SEC;
        cout << "SpawnOrder: Use " << (t2 - t1) << "s / " << levelData["entities"].size() << " entities" << endl;
    }

    void clearOutdatedParticle(double currTime) {
        for (auto it = activeEffects.begin(); it != activeEffects.end(); ) {
            if (!it->second.loop && (currTime < it->second.stTime || currTime > it->second.stTime + it->second.duration)) 
                it = activeEffects.erase(it);
            else it++;
        }
    }

    void initializeCycle() {
        // 激活实体
        initializeOrder.clear();
        updateSequentialOrder.clear();
        touchOrder.clear();
        updateParallelOrder.clear();
        while (true) {
            if (activePointer >= spawnQueue.size()) break;
            int eid = spawnQueue[activePointer];
            int aid = entityAid[eid];
            if (aid == -1) {
                activePointer++;
                continue;
            }
            entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            setCallbackName("shouldSpawn");
            startEntity(eid);
            bool shouldSpawn = engineData["archetypes"][aid].isMember("shouldSpawn") ? RunCode(engineData["archetypes"][aid]["shouldSpawn"]["index"].asInt()) : 1;
            if (!shouldSpawn) {
                endEntity();
                break;
            }
            initializeOrder.push_back(eid);
            endEntity();
            activeEntities.insert(eid);
            activePointer++;
        }
        for (auto v : activeEntities) updateSequentialOrder.push_back(v), touchOrder.push_back(v), updateParallelOrder.push_back(v);
    }

    void runInitialize() {
        setCallbackName("initialize");
        sort(initializeOrder.begin(), initializeOrder.end(), cmp);
        for (auto eid : initializeOrder) {
            int aid = entityAid[eid];
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            directSet(4003, 2, 1);
            RunCode(engineData["archetypes"][aid]["initialize"]["index"].asInt());
            endEntity();
        }
    }

    void runUpdateSequential() {
        setCallbackName("updateSequential");
        sort(updateSequentialOrder.begin(), updateSequentialOrder.end(), cmp);
        for (auto eid : updateSequentialOrder) {
            int aid = entityAid[eid];
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            RunCode(engineData["archetypes"][aid]["updateSequential"]["index"].asInt());
            endEntity();
        }
    }

    void runTouch() {
        setCallbackName("touch");
        sort(touchOrder.begin(), touchOrder.end(), cmp);
        for (auto eid : touchOrder) {
            int aid = entityAid[eid];
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            RunCode(engineData["archetypes"][aid]["touch"]["index"].asInt());
            endEntity();
        }
    }

    void runUpdateParallel() {
        setCallbackName("updateParallel");
        sort(updateParallelOrder.begin(), updateParallelOrder.end(), cmp);
        for (auto eid : updateParallelOrder) {
            int aid = entityAid[eid];
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            RunCode(engineData["archetypes"][aid]["updateParallel"]["index"].asInt());
            endEntity();
        }
    }

    void destroyEntity() {
        set<int> oldActiveEntities = activeEntities;
        terminateOrder.clear();
        for (auto eid : oldActiveEntities) {
            startEntity(eid);
            if (directGet(4004, 0)) {
                terminateOrder.push_back(eid);
                activeEntities.erase(eid);
            }
            endEntity();
        }
        sort(terminateOrder.begin(), terminateOrder.end(), cmp);
    }

    void runTerminate() {
        setCallbackName("terminate");
        for (auto eid : terminateOrder) {
            int aid = entityAid[eid];
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            startEntity(eid);
            ::currTime = directGet(1001, 0);
            directSet(4003, 2, 2);
            targetActiveCount -= engineData["archetypes"][aid]["hasInput"].asBool();
            RunCode(engineData["archetypes"][aid]["terminate"]["index"].asInt());
            endEntity();
        }
    }

    void solveNewSpawn() {
        for (auto item : newSpawnList) {
            int id = item.first;
            vector<double> memory = item.second;
            int aid = entityAid[id];
            startEntity(id);
            for (int j = 0; j < 64; j++) directSet(4000, j, 0);
            for (int j = 0; j < min(64, int(memory.size())); j++) directSet(4000, j, memory[j]);
            for (int j = 0; j < 32; j++) directSet(4001, j, 0);
            for (int j = 0; j < 32; j++) directSet(4002, j, 0);
            directSet(4003, 0, id);
            directSet(4003, 1, aid);
            directSet(4003, 2, 0);
            directSet(4004, 0, 0);
            directSet(4005, 0, 0);
            directSet(4005, 1, 0);
            directSet(4005, 2, -1);
            directSet(4005, 3, 0);

            entityId = id;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            setCallbackName("preprocess");
            RunCode(engineData["archetypes"][aid]["preprocess"]["index"].asInt());
            endEntity();
            initializeOrder.push_back(id);
            activeEntities.insert(id);
        }
        newSpawnList.clear();
    }

    void solveGLEvent(double time) {
        pthread_mutex_lock(&touchMtx);
        for (int i = 0; i < glEventsCount; i++) glEvents[i](time);
        pthread_mutex_unlock(&touchMtx);
        clearGLEvent();
    }

    void solveTouch() {
        destroyMemory(1002);
        setMemory(1002, 15 * touches.size());
        int index = 0;
        for (auto v : touches) {
            directSet(1002, index * 15 + 0, v.first);
            directSet(1002, index * 15 + 1, v.second.started);
            directSet(1002, index * 15 + 2, v.second.ended);
            directSet(1002, index * 15 + 3, v.second.t);
            directSet(1002, index * 15 + 4, v.second.st);
            directSet(1002, index * 15 + 5, v.second.x);
            directSet(1002, index * 15 + 6, v.second.y);
            directSet(1002, index * 15 + 7, v.second.sx);
            directSet(1002, index * 15 + 8, v.second.sy);
            directSet(1002, index * 15 + 9, v.second.dx);
            directSet(1002, index * 15 + 10, v.second.dy);
            directSet(1002, index * 15 + 11, v.second.vx);
            directSet(1002, index * 15 + 12, v.second.vy);
            directSet(1002, index * 15 + 13, v.second.vr);
            directSet(1002, index * 15 + 14, v.second.vw);
            index++;
        }
    }

    void main() {
        custom_onresize = [&](int, int) { directSet(1000, 1, aspectRadio); };
        RuntimeSkinTransformId = 1003;
        RuntimeParticleTransformId = 1004;
        ::customSpawn = customSpawn;
        setEnv(engineData["archetypes"].size(), levelData["entities"].size(), options.size(), engineData["buckets"].size());
        setMode("play");
        initNodes(engineData["nodes"]);

        solveArchetypes();
        prepareBlocks();
        solveBlocks();
        // optimizeNodes({ 2002, 3000 });

        for (int i = 0; i < levelData["entities"].size(); i++) {
            if (aids.find(levelData["entities"][i]["archetype"].asString()) == aids.end()) continue;
            preprocessOrder.push_back(i), spawnOrderOrder.push_back(i);
        }
        runPreprocess();
        runSpawnOrder();
        // return 0;

        // optimizeNodes({ 1000, 1006, 1007, 2001, 2002, 2003, 2004, 2005, 3000, 5000 });

        // 处理激活队列
        for (int i = 0; i < levelData["entities"].size(); i++) spawnQueue.push_back(i);
        sort(spawnQueue.begin(), spawnQueue.end(), [&](int a, int b){ return spawnOrder[a] == spawnOrder[b] ? a < b : spawnOrder[a] < spawnOrder[b]; });

        stTime = 1.0 * clock2() / CLOCKS_PER_SEC + 3; double lastTime = stTime - 3;
        int currFrame = -targetFPS * 3;
        vector<double> totalTimes;
        while (true) {
            glClear(GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);

            int tmp = cnt;
            double currTime = 1.0 * clock2() / CLOCKS_PER_SEC, tmpStTime = stTime;
            drawLists.clear();
            time_t t1 = clock2();
            solveGLEvent(currTime - stTime);
            freshTouch(currTime - stTime);
            
            directSet(1001, 0, currTime - tmpStTime);
            directSet(1001, 1, currTime - lastTime);
            directSet(1001, 2, TimeToScaledTime(currTime - tmpStTime));
            directSet(1001, 3, touches.size());
            directSet(1001, 4, needSkip);
            solveNewSpawn();
            
            solveTouch();
            clearOutdatedParticle(currTime - tmpStTime);
            initializeCycle();
            runInitialize();
            runUpdateSequential();
            if (touches.size()) runTouch();
            runUpdateParallel();
            destroyEntity();
            runTerminate();
            clearTouch();

            sort(drawLists.begin(), drawLists.end(), [](auto a, auto b){ 
                return a.z1 == b.z1 ? (
                    a.z2 == b.z2 ? (
                        a.z3 == b.z3 ? a.z4 < b.z4 : a.z3 < b.z3
                    ) : a.z2 < b.z2
                ) : a.z1 < b.z1;
            });
            renderDrawLists = drawLists;
            display(currTime - tmpStTime);
            glfwSwapBuffers(window);
            glfwPollEvents();
            time_t t2 = clock2() - (stTime - tmpStTime) * CLOCKS_PER_SEC;

            totalTimes.push_back(1.0 * (t2 - t1) / CLOCKS_PER_SEC);
            double totalTime = 0;
            for (int i = totalTimes.size() - 1; i >= totalTimes.size() - targetFPS && i >= 0; i--) totalTime += totalTimes[i];
            usleep(max(0.0, 1.0 / targetFPS - 1.0 * (t2 - t1) / CLOCKS_PER_SEC) * 1000 * 1000);
            cout << "frame: " << currFrame << " | time: "
                << fixed << setprecision(3)
                << currTime - tmpStTime << "s | cost: " 
                << 1.0 * (t2 - t1) / CLOCKS_PER_SEC * 1000 << "ms | " 
                << (1.0 / (t2 - t1) * CLOCKS_PER_SEC) << "fps | avg: " 
                << (1.0 / (totalTime / min(targetFPS, (int)totalTimes.size()))) << "fps | active: "
                << targetActiveCount << " | calc: "
                << cnt - tmp << "nodes" << endl;
            lastTime = currTime; currFrame++;

            if (shouldStop) {
                if (needSkip) needSkip = false;
                stopped = true;
                currEntityId = 0;
                double frozenTime = 1.0 * clock2() / CLOCKS_PER_SEC;
                while (shouldStop) commandLine();
                double unfrozenTime = 1.0 * clock2() / CLOCKS_PER_SEC;
                stTime += unfrozenTime - frozenTime;
                stopped = false;
                needSkip = false; // 没搞清楚 Play 模式模式怎么 skip
            }

            if (needSkip) {
                double unfrozenTime = 1.0 * clock2() / CLOCKS_PER_SEC;
                stTime = unfrozenTime - skipTime;
                shouldStop = true;
                activeEffects.clear();
            }

            if (targetActiveCount == 0) break;
        }
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}