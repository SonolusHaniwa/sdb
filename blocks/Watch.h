#ifndef WatchBlocks_H
#define WatchBlocks_H

map<int, set<string> > readMapWatch = {
	{ 1000, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 1001, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 1002, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 1003, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 1004, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 1005, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 1006, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 2000, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 2001, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 2002, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 2003, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 2004, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 2005, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 3000, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 4000, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate" } },
	{ 4001, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate" } },
	{ 4002, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate" } },
	{ 4003, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate" } },
	{ 4004, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate" } },
	{ 4005, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 4006, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 4101, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 4102, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 4103, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 4105, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 4106, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 5000, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 5001, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } },
	{ 10000, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } }
};
map<int, set<string> > writeMapWatch = {
	{ 1000, { "preprocess" } },
	{ 1001, {  } },
	{ 1002, { "preprocess", "updateSequential" } },
	{ 1003, { "preprocess", "updateSequential" } },
	{ 1004, { "preprocess", "updateSequential" } },
	{ 1005, { "preprocess" } },
	{ 1006, { "preprocess" } },
	{ 2000, { "preprocess", "updateSequential" } },
	{ 2001, { "preprocess" } },
	{ 2002, {  } },
	{ 2003, { "preprocess" } },
	{ 2004, { "preprocess" } },
	{ 2005, { "preprocess" } },
	{ 3000, {  } },
	{ 4000, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate" } },
	{ 4001, { "preprocess" } },
	{ 4002, { "preprocess", "updateSequential" } },
	{ 4003, {  } },
	{ 4004, { "preprocess" } },
	{ 4005, { "preprocess" } },
	{ 4006, { "preprocess" } },
	{ 4101, { "preprocess" } },
	{ 4102, { "preprocess", "updateSequential" } },
	{ 4103, {  } },
	{ 4105, { "preprocess" } },
	{ 4106, { "preprocess" } },
	{ 5000, { "preprocess" } },
	{ 5001, { "preprocess" } },
	{ 10000, { "preprocess", "spawnTime", "despawnTime", "initialize", "updateSequential", "updateParallel", "terminate", "updateSpawn" } }
};
void initWatchMemory() {
	setMemory(1000, 9);
	setMemory(1001, 4);
	setMemory(1002, 16);
	setMemory(1003, 16);
	setMemory(1004, 8);
	setMemory(1005, 100);
	setMemory(1006, 12);
	setMemory(2000, 4096);
	setMemory(2001, 4096);
	setMemory(2002, 1 * optionCount);
	setMemory(2003, 6 * bucketCount);
	setMemory(2004, 12);
	setMemory(2005, 8);
	setMemory(3000, 0);
	setMemory(4000, 64);
	setMemory(4001, 32);
	setMemory(4002, 32);
	setMemory(4003, 3);
	setMemory(4004, 3);
	setMemory(4005, 1);
	setMemory(4006, 4);
	setMemory(4101, 32 * entityCount);
	setMemory(4102, 32 * entityCount);
	setMemory(4103, 3 * entityCount);
	setMemory(4105, 1 * entityCount);
	setMemory(4106, 4 * entityCount);
	setMemory(5000, 4 * archetypeCount);
	setMemory(5001, 1 * archetypeCount);
	setMemory(10000, 4096);
}

#endif
