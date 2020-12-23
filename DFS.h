#ifndef E_DFS
#define E_DFS

#include "puzzle.h"

class DFS : public puzzle
{
private:
	int MAX = 50;
    bool dfs(int stateNum, int idx, int d_step) {
        std::vector<int> stateArr = num2arr(stateNum);
        if (d_step >= 50 || visited.count(stateNum)) return false;
        visited.insert(stateNum);
        if (stateNum == 123456780) {
            solved = true;
            return true;
        }
        count++;

        for (int i = 0; i < 4; ++i) {
            if (idx % 3 == 0 && i == 1) continue;
            if (idx % 3 == 2 && i == 0) continue;
            int next_idx = idx + dd[i];
            if (next_idx >= 0 && next_idx < 9) {
                std::swap(stateArr[idx], stateArr[next_idx]);
                int tmp = arr2num(stateArr);
                parent[tmp] = stateNum;
                if (dfs(tmp, next_idx, d_step+1)) return true;
                parent.erase(tmp);
                std::swap(stateArr[idx], stateArr[next_idx]);
            }
        }
        return false;
    }
public:
	void run() {
        dfs(arr2num(state), zeroIndex(state), 0);
	}
};

#endif

