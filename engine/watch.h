namespace watch {
    const int targetFPS = 120;
    map<string, int> aids;
    map<string, map<string, int> > importData;
    vector<int> entityAid;
    vector<vector<int> > callbackOrder;
    vector<int> preprocessOrder, spawnTimeOrder, despawnTimeOrder;
    vector<int> initializeOrder, updateSequentialOrder, updateParallelOrder;
    vector<int> terminateOrder;

    vector<double**> newSpawnedMemory;
    
    void startEntity(int i) {
        if (i < entityCount) for (int j = 0; j < 7; j++) linkMemory(4000 + j, memorySize[4100 + j] / entityCount, 4100 + j, memorySize[4100 + j] / entityCount * i);
        else for (int j = 0; j < 7; j++) linkMemory(4000 + j, memorySize[4100 + j] / entityCount, newSpawnedMemory[i - entityCount][j], 0);
    }
    void endEntity() {
        for (int j = 0; j < 7; j++) destroyMemory(4000 + j);
    }
    bool cmp(int a, int b) {
        int aidA = entityAid[a];
        int aidB = entityAid[b];
        double orderA = aidA == -1 ? 0 : callbackOrder[aidA][callbackNameId], 
               orderB = aidB == -1 ? 0 : callbackOrder[aidB][callbackNameId];
        return orderA == orderB ? a < b : orderA < orderB;
    };

    vector<pair<int, vector<double> > > newSpawnList;
    function<void(double, vector<double>)> customSpawn = [](double id, vector<double> memory){
        if (id < 0 || id >= engineData["archetypes"].size()) return;
        int aid = id; 
        double** newMemory = new double*[7];
        for (int i = 0; i < 7; i++) newMemory[i] = new double[memorySize[4100 + i] / entityCount];
        newSpawnedMemory.push_back(newMemory);
        entityAid.push_back(aid);
        newSpawnList.push_back({ entityAid.size() - 1, memory });
        // cout << "New Spawn: Entity id = " << id << ", archetype = \"Spawned: " << engineData["archetypes"][aid]["name"].asString() << "\"" << endl;
    };

    void solveArchetypes() {
        for (int i = 0; i < engineData["archetypes"].size(); i++) {
            string name = engineData["archetypes"][i]["name"].asString();
            aids[name] = i;
            importData[name] = {};
            for (int j = 0; j < engineData["archetypes"][i]["imports"].size(); j++) {
                int index = engineData["archetypes"][i]["imports"][j]["index"].asInt();
                string var = engineData["archetypes"][i]["imports"][j]["name"].asString();
                importData[name][var] = index;
            }
        }
        callbackOrder.resize(engineData["archetypes"].size());
        for (int i = 0; i < engineData["archetypes"].size(); i++) {
            callbackOrder[i].resize(callbackIdCount);
            callbackOrder[i][callbackId["preprocess"]] = engineData["archetypes"][i].isMember("preprocess") ? engineData["archetypes"][i]["preprocess"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["spawnTime"]] = engineData["archetypes"][i].isMember("spawnTime") ? engineData["archetypes"][i]["spawnTime"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["despawnTime"]] = engineData["archetypes"][i].isMember("despawnTime") ? engineData["archetypes"][i]["despawnTime"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["initialize"]] = engineData["archetypes"][i].isMember("initialize") ? engineData["archetypes"][i]["initialize"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["updateSequential"]] = engineData["archetypes"][i].isMember("updateSequential") ? engineData["archetypes"][i]["updateSequential"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["updateParallel"]] = engineData["archetypes"][i].isMember("updateParallel") ? engineData["archetypes"][i]["updateParallel"]["order"].asDouble() : 0;
            callbackOrder[i][callbackId["terminate"]] = engineData["archetypes"][i].isMember("terminate") ? engineData["archetypes"][i]["terminate"]["order"].asDouble() : 0;
        }
    }
    
    void prepareBlocks() {
        setMemory(4100, 64 * entityCount);
        setMemory(4104, 3 * entityCount);
        for (int i = 0; i < 7; i++) destroyMemory(4000 + i);
        
        directSet(1000, 0, 1);
        directSet(1000, 1, aspectRadio);
        directSet(1000, 2, 0);
        directSet(1000, 3, 0);
        directSet(1000, 4, 0);
        for (int i = 0; i < 16; i++) directSet(1002, i, 0);
        directSet(1002, 0, 1);
        directSet(1002, 5, 1);
        directSet(1002, 10, 1);
        directSet(1002, 15, 1);
        for (int i = 0; i < 16; i++) directSet(1003, i, 0);
        directSet(1003, 0, 1);
        directSet(1003, 5, 1);
        directSet(1003, 10, 1);
        directSet(1003, 15, 1);
        for (int i = 0; i < 12; i++) directSet(1006, i, 1);
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

            startEntity(i);
            for (int j = 0; j < 64; j++) directSet(4000, j, 0);
            for (int j = 0; j < 32; j++) directSet(4001, j, 0);
            for (int j = 0; j < 32; j++) directSet(4002, j, 0);
            if (aid != -1) for (int j = 0; j < levelData["entities"][i]["data"].size(); j++) {
                string name = levelData["entities"][i]["data"][j]["name"].asString();
                double value = levelData["entities"][i]["data"][j].isMember("ref")
                    ? refs[levelData["entities"][i]["data"][j]["ref"].asString()]
                    : levelData["entities"][i]["data"][j]["value"].asDouble();
                if (importData[aname].count(name) == 0) continue;
                int index = importData[aname][name];
                if (overflowMemory(4001, index)) continue;
                directSet(4001, index, value);
            }
            directSet(4003, 0, i);
            directSet(4003, 1, aid);
            directSet(4003, 2, 0);
            directSet(4004, 0, 0);
            directSet(4004, 1, -1);
            directSet(4004, 2, 0);
            directSet(4005, 0, 0);
            directSet(4006, 0, 0);
            directSet(4006, 1, 0);
            directSet(4006, 2, 0);
            directSet(4006, 3, 0);
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
            if (aid == -1) continue;
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

    void runSpawnTime() {
        spawnTime.resize(levelData["entities"].size());
        double t1 = 1.0 * clock2() / CLOCKS_PER_SEC;
        setCallbackName("spawnTime");
        sort(spawnTimeOrder.begin(), spawnTimeOrder.end(), cmp);
        for (auto eid : spawnTimeOrder) {
            int aid = entityAid[eid];
            if (aid == -1) continue;
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            double time = engineData["archetypes"][aid].isMember("spawnTime") ? RunCode(engineData["archetypes"][aid]["spawnTime"]["index"].asInt()) : 0;
            spawnTime[entityId] = time;
            endEntity();
        }
        double t2 = 1.0 * clock2() / CLOCKS_PER_SEC;
        cout << "SpawnTime: Use " << (t2 - t1) << "s / " << levelData["entities"].size() << " entities" << endl;
    }

    void runDespawnTime() {
        despawnTime.resize(levelData["entities"].size());
        double t1 = 1.0 * clock2() / CLOCKS_PER_SEC;
        setCallbackName("despawnTime");
        sort(despawnTimeOrder.begin(), despawnTimeOrder.end(), cmp);
        for (auto eid : despawnTimeOrder) {
            int aid = entityAid[eid];
            if (aid == -1) continue;
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            double time = engineData["archetypes"][aid].isMember("despawnTime") ? RunCode(engineData["archetypes"][aid]["despawnTime"]["index"].asInt()) : 0;
            despawnTime[entityId] = time;
            endEntity();
        }
        double t2 = 1.0 * clock2() / CLOCKS_PER_SEC;
        cout << "DespawnTime: Use " << (t2 - t1) << "s / " << levelData["entities"].size() << " entities" << endl;
    }

    void clearOutdatedParticle(double currTime) {
        for (auto it = activeEffects.begin(); it != activeEffects.end(); ) {
            if (!it->second.loop && (currTime < it->second.stTime || currTime > it->second.stTime + it->second.duration)) 
                it = activeEffects.erase(it);
            else it++;
        }
    }

    void initializeCycle(double currTime) {
        // 激活实体
        terminateOrder.clear();
        initializeOrder.clear();
        updateSequentialOrder.clear();
        updateParallelOrder.clear();
        for (int i = 0; i < entityAid.size(); i++) {
            bool activeNow = activeEntities.count(i);
            bool activeNext = spawnTime[i] <= currTime && currTime <= despawnTime[i];
            // if (i <= 5) cout << activeNow << " " << activeNext << " " << spawnTime[i] << " " << currTime << " " << despawnTime[i] << endl;
            if (activeNow && activeNext) ;
            else if (activeNow && !activeNext) terminateOrder.push_back(i), activeEntities.erase(i);
            else if (!activeNow && activeNext) initializeOrder.push_back(i), activeEntities.insert(i);
            else if (!activeNow && !activeNext) ;
        }
        for (auto v : activeEntities) updateSequentialOrder.push_back(v), updateParallelOrder.push_back(v);
    }

    void runTerminate() {
        setCallbackName("terminate");
        sort(terminateOrder.begin(), terminateOrder.end(), cmp);
        for (auto eid : terminateOrder) {
            int aid = entityAid[eid];
            if (aid == -1) continue;
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            startEntity(eid);
            ::currTime = directGet(1001, 0);
            directSet(4003, 2, 0);
            RunCode(engineData["archetypes"][aid]["terminate"]["index"].asInt());
            endEntity();
        }
    }

    void runInitialize() {
        setCallbackName("initialize");
        sort(initializeOrder.begin(), initializeOrder.end(), cmp);
        for (auto eid : initializeOrder) {
            int aid = entityAid[eid];
            if (aid == -1) continue;
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
            if (aid == -1) continue;
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            RunCode(engineData["archetypes"][aid]["updateSequential"]["index"].asInt());
            endEntity();
        }
    }

    void runUpdateParallel() {
        setCallbackName("updateParallel");
        sort(updateParallelOrder.begin(), updateParallelOrder.end(), cmp);
        for (auto eid : updateParallelOrder) {
            int aid = entityAid[eid];
            if (aid == -1) continue;
            currEntityId = entityId = eid;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            startEntity(eid);
            RunCode(engineData["archetypes"][aid]["updateParallel"]["index"].asInt());
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
            directSet(4004, 1, -1);
            directSet(4004, 2, 0);
            directSet(4005, 0, 0);
            directSet(4006, 0, 0);
            directSet(4006, 1, 0);
            directSet(4006, 2, 0);
            directSet(4006, 3, 0);

            entityId = id;
            archetypeName = engineData["archetypes"][aid]["name"].asString();
            ::currTime = directGet(1001, 0);
            setCallbackName("preprocess");
            RunCode(engineData["archetypes"][aid]["preprocess"]["index"].asInt());
            setCallbackName("spawnTime");
            double time = engineData["archetypes"][aid].isMember("spawnTime") ? RunCode(engineData["archetypes"][aid]["spawnTime"]["index"].asInt()) : 0;
            spawnTime.push_back(time);
            setCallbackName("despawnTime");
            time = engineData["archetypes"][aid].isMember("despawnTime") ? RunCode(engineData["archetypes"][aid]["despawnTime"]["index"].asInt()) : 0;
            despawnTime.push_back(time);
            endEntity();
        }
        newSpawnList.clear();
    }

    void main() {
        custom_onresize = [&](int, int) { directSet(1000, 1, aspectRadio); };
        RuntimeSkinTransformId = 1002;
        RuntimeParticleTransformId = 1003;
        ::customSpawn = customSpawn;
        setEnv(engineData["archetypes"].size(), levelData["entities"].size(), options.size(), engineData["buckets"].size());
        setMode("watch");
        initNodes(engineData["nodes"]);

        solveArchetypes();
        prepareBlocks();
        solveBlocks();

        for (int i = 0; i < levelData["entities"].size(); i++) {
            if (aids.find(levelData["entities"][i]["archetype"].asString()) == aids.end()) continue;
            preprocessOrder.push_back(i), spawnTimeOrder.push_back(i), despawnTimeOrder.push_back(i);
        }
        runPreprocess();
        runSpawnTime();
        runDespawnTime();

        double stTime = 1.0 * clock2() / CLOCKS_PER_SEC + 3, lastTime = stTime - 3;
        int currFrame = -targetFPS * 3;
        vector<double> totalTimes;
        while (true) {
            glClear(GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            
            int tmp = cnt;
            double currTime = 1.0 * clock2() / CLOCKS_PER_SEC;
            drawLists.clear();
            time_t t1 = clock2();
            directSet(1001, 0, currTime - stTime);
            directSet(1001, 1, currTime - lastTime);
            directSet(1001, 2, TimeToScaledTime(currTime - stTime));
            directSet(1001, 3, needSkip);
            solveNewSpawn();

            setCallbackName("updateSpawn");
            double customCurrentTime = RunCode(engineData["updateSpawn"].asInt());

            clearOutdatedParticle(currTime - stTime);
            initializeCycle(customCurrentTime);
            runTerminate();
            runInitialize();
            runUpdateSequential();
            runUpdateParallel();
            
            sort(drawLists.begin(), drawLists.end(), [](auto a, auto b){ return a.z < b.z; });
            renderDrawLists = drawLists;
            display(currTime - stTime);
            glfwSwapBuffers(window);
            glfwPollEvents();
            time_t t2 = clock2();

            totalTimes.push_back(1.0 * (t2 - t1) / CLOCKS_PER_SEC);
            double totalTime = 0;
            for (int i = totalTimes.size() - 1; i >= totalTimes.size() - targetFPS && i >= 0; i--) totalTime += totalTimes[i];
            usleep(max(0.0, 1.0 / targetFPS - 1.0 * (t2 - t1) / CLOCKS_PER_SEC) * 1000 * 1000);
            cout << "frame: " << currFrame << " | time: "
                << fixed << setprecision(3)
                << currTime - stTime << "s | spawn: "
                << customCurrentTime << "s | cost: " 
                << 1.0 * (t2 - t1) / CLOCKS_PER_SEC * 1000 << "ms | " 
                << (1.0 / (t2 - t1) * CLOCKS_PER_SEC) << "fps | avg: " 
                << (1.0 / (totalTime / min(targetFPS, (int)totalTimes.size()))) << "fps | active: "
                << activeEntities.size() << " | calc: "
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
            }

            if (needSkip) {
                double unfrozenTime = 1.0 * clock2() / CLOCKS_PER_SEC;
                stTime = unfrozenTime - skipTime;
                shouldStop = true;
                activeEffects.clear();
            }
        }
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}