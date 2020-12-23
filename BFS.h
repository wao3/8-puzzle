#ifndef E_BFS
#define E_BFS

#include "puzzle.h"
class BFS : public puzzle
{
private:
    bool bfs() {
        std::queue<int> q;
        q.push(arr2num(state));
        while (q.size() && !solved) {
            int n = q.size();
            while (n--) {
                count++;
                int now = q.front();
                if (now == ANSNUM) {
                    solved = true;
                    return true;
                }
                std::vector<int> arr = num2arr(now);
                q.pop();
                int idx = zeroIndex(arr);
                for (int i = 0; i < 4; ++i) {
                    if (idx % 3 == 0 && i == 1) continue;
                    if (idx % 3 == 2 && i == 0) continue;
                    int next_idx = idx + dd[i];
                    if (next_idx >= 0 && next_idx < 9) {
                        std::swap(arr[idx], arr[next_idx]);
                        int tmp = arr2num(arr);
                        parent[tmp] = now;
                        q.push(tmp);
                        std::swap(arr[idx], arr[next_idx]);
                    }
                }
            }
        }
        return false;
    }
public:
    void run() {
        bfs();
    }
};
#endif
