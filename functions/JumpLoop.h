#ifndef Functions_JumpLoop_H
#define Functions_JumpLoop_H

double JumpLoop(const vector<double> &branch) {
	int nxtBranch = 0;
	while (true) {
		if (nxtBranch < 0 || nxtBranch >= branch.size()) return 0;
		updateCurrParam(nxtBranch);
		double res = RunCode(branch[nxtBranch]);
		if (breakCount) return 0;
		if (nxtBranch == branch.size() - 1) return res;
		nxtBranch = res;
	}
}

#endif
