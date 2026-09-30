#ifndef PlayBlocks_H
#define PlayBlocks_H

map<int, set<string> > readMapPlay = {
	{ 1000, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 1001, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 1002, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 1003, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 1004, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 1005, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 1006, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 1007, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 2000, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 2001, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 2002, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 2003, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 2004, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 2005, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 3000, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4000, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4001, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4002, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4003, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4004, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4005, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4006, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4007, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4101, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4102, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4103, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4106, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4107, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 5000, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 5001, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 10000, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } }
};
map<int, set<string> > writeMapPlay = {
	{ 1000, { "preprocess" } },
	{ 1001, {  } },
	{ 1002, {  } },
	{ 1003, { "preprocess", "updateSequential", "touch" } },
	{ 1004, { "preprocess", "updateSequential", "touch" } },
	{ 1005, { "preprocess", "updateSequential", "touch" } },
	{ 1006, { "preprocess" } },
	{ 1007, { "preprocess" } },
	{ 2000, { "preprocess", "updateSequential", "touch" } },
	{ 2001, { "preprocess" } },
	{ 2002, {  } },
	{ 2003, { "preprocess" } },
	{ 2004, { "preprocess" } },
	{ 2005, { "preprocess" } },
	{ 3000, {  } },
	{ 4000, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4001, { "preprocess" } },
	{ 4002, { "preprocess", "updateSequential", "touch" } },
	{ 4003, {  } },
	{ 4004, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4005, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } },
	{ 4006, { "preprocess" } },
	{ 4007, { "preprocess" } },
	{ 4101, { "preprocess" } },
	{ 4102, { "preprocess", "updateSequential", "touch" } },
	{ 4103, {  } },
	{ 4106, { "preprocess" } },
	{ 4107, { "preprocess" } },
	{ 5000, { "preprocess" } },
	{ 5001, { "preprocess" } },
	{ 10000, { "preprocess", "spawnOrder", "shouldSpawn", "initialize", "updateSequential", "touch", "updateParallel", "terminate" } }
};
void initPlayMemory() {
	setMemory(1000, 9);
	setMemory(1001, 5);
	setMemory(1002, 0);
	setMemory(1003, 16);
	setMemory(1004, 16);
	setMemory(1005, 8);
	setMemory(1006, 80);
	setMemory(1007, 10);
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
	setMemory(4004, 1);
	setMemory(4005, 5);
	setMemory(4006, 1);
	setMemory(4007, 4);
	setMemory(4101, 32 * entityCount);
	setMemory(4102, 32 * entityCount);
	setMemory(4103, 3 * entityCount);
	setMemory(4106, 1 * entityCount);
	setMemory(4107, 4 * entityCount);
	setMemory(5000, 4 * archetypeCount);
	setMemory(5001, 1 * archetypeCount);
	setMemory(10000, 4096);
}

#endif
