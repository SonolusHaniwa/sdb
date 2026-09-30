#ifndef TutorialBlocks_H
#define TutorialBlocks_H

map<int, set<string> > readMapTutorial = {
	{ 1000, { "preprocess", "navigate", "update" } },
	{ 1001, { "preprocess", "navigate", "update" } },
	{ 1002, { "preprocess", "navigate", "update" } },
	{ 1003, { "preprocess", "navigate", "update" } },
	{ 1004, { "preprocess", "navigate", "update" } },
	{ 1005, { "preprocess", "navigate", "update" } },
	{ 1006, { "preprocess", "navigate", "update" } },
	{ 2000, { "preprocess", "navigate", "update" } },
	{ 2001, { "preprocess", "navigate", "update" } },
	{ 2002, { "preprocess", "navigate", "update" } },
	{ 3000, { "preprocess", "navigate", "update" } },
	{ 10000, { "preprocess", "navigate", "update" } }
};
map<int, set<string> > writeMapTutorial = {
	{ 1000, { "preprocess" } },
	{ 1001, {  } },
	{ 1002, { "preprocess", "navigate", "update" } },
	{ 1003, { "preprocess", "navigate", "update" } },
	{ 1004, { "preprocess", "navigate", "update" } },
	{ 1005, { "preprocess" } },
	{ 1006, { "preprocess" } },
	{ 2000, { "preprocess", "navigate", "update" } },
	{ 2001, { "preprocess" } },
	{ 2002, { "preprocess", "navigate", "update" } },
	{ 3000, {  } },
	{ 10000, { "preprocess", "navigate", "update" } }
};
void initTutorialMemory() {
	setMemory(1000, 7);
	setMemory(1001, 3);
	setMemory(1002, 16);
	setMemory(1003, 16);
	setMemory(1004, 8);
	setMemory(1005, 36);
	setMemory(1006, 6);
	setMemory(2000, 4096);
	setMemory(2001, 4096);
	setMemory(2002, 1);
	setMemory(3000, 0);
	setMemory(10000, 4096);
}

#endif
