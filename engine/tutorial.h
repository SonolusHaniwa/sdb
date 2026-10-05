namespace tutorial {
    const int targetFPS = 120;

    void clearOutdatedParticle(double currTime) {
        for (auto it = activeEffects.begin(); it != activeEffects.end(); ) {
            if (!it->second.loop && (currTime < it->second.stTime || currTime > it->second.stTime + it->second.duration)) 
                it = activeEffects.erase(it);
            else it++;
        }
    }
    
    void main() {
        RuntimeSkinTransformId = 1002;
        RuntimeParticleTransformId = 1002;
        setEnv(0, 0, 0, 0);
        setMode("tutorial");
        initNodes(engineData["nodes"]);

        directSet(1000, 0, 1);
        directSet(1000, 1, 1.0 * width / height);
        directSet(1000, 2, 0);
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
        for (int i = 0; i < 6; i++) directSet(1006, i, 1);
        directSet(2002, 0, -1);

        setCallbackName("preprocess");
        RunCode(engineData["preprocess"].asInt());

        stTime = 1.0 * clock2() / CLOCKS_PER_SEC; double lastTime = stTime;
        vector<double> totalTimes;
        while (true) {
            glClear(GL_DEPTH_BUFFER_BIT);
            glClearColor(0.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            
            int tmp = cnt;
            double currTime = 1.0 * clock2() / CLOCKS_PER_SEC, tmpStTime = stTime;
            drawLists.clear();
            time_t t1 = clock2();
            directSet(1001, 0, currTime - tmpStTime);
            directSet(1001, 1, currTime - lastTime);
            ::currTime = currTime - tmpStTime;
            clearOutdatedParticle(currTime - tmpStTime);

            setCallbackName("update");
            RunCode(engineData["update"].asInt());
            
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
            cout << "time: " << fixed << setprecision(3) << currTime - tmpStTime << "s | cost: " 
                << 1.0 * (t2 - t1) / CLOCKS_PER_SEC * 1000 << "ms | " 
                << (1.0 / (t2 - t1) * CLOCKS_PER_SEC) << "fps | avg: " 
                << (1.0 / (totalTime / min(targetFPS, (int)totalTimes.size()))) << "fps | calc: "
                << cnt - tmp << "nodes" << endl;
            lastTime = currTime;

            if (shouldStop) {
                stopped = true;
                currEntityId = 0;
                double frozenTime = 1.0 * clock2() / CLOCKS_PER_SEC;
                while (shouldStop) commandLine();
                double unfrozenTime = 1.0 * clock2() / CLOCKS_PER_SEC;
                stTime += unfrozenTime - frozenTime;
                stopped = false;
            }
        };
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}