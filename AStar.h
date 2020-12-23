#ifndef E_ASTAR
#define E_ASTAR

#include "puzzle.h"

int manhattan[10][10] = {
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1, 0, 1, 2, 1, 2, 3, 2, 3, 4},
    {-1, 1, 0, 1, 2, 1, 2, 3, 2, 3},
    {-1, 2, 1, 0, 3, 2, 1, 4, 3, 2},
    {-1, 1, 2, 3, 0, 1, 2, 1, 2, 3},
    {-1, 2, 1, 2, 1, 0, 1, 2, 1, 2},
    {-1, 3, 2, 1, 2, 1, 0, 3, 2, 1},
    {-1, 2, 3, 4, 1, 2, 3, 0, 1, 2},
    {-1, 3, 2, 3, 2, 1, 2, 1, 0, 1},
    {-1, 4, 3, 2, 3, 2, 1, 2, 1, 0}
};

class AStar : public puzzle
{
private:
    static int AScore(std::vector<int> arr, int s) {
        int score = s;
        for (int i = 0; i < 9; ++i) {
            score += manhattan[i + 1][arr[i]];
        }
        return score;
    }

    struct Node {
        int num, step;
        Node(int n, int s): num(n), step(s) {}
        bool operator<(Node b) {
            int as = AScore(num2arr(num), step);
            int bs = AScore(num2arr(b.num), b.step);
            return as > bs;
        }
    };

    int runAStar(int stateNum) {
        std::priority_queue<Node, std::vector<Node>> q;
        Node root = Node(stateNum, 0);
        q.push(root);
        while (q.size() && !solved) {
            int n = q.size();
            while (n--) {
                Node now = q.top();
                visited.insert(now.num);
                if (now.num == ANSNUM) return true;
                std::vector<int> arr = num2arr(now.num);
                q.pop();
                int idx = zeroIndex(arr);
                for (int i = 0; i < 4; ++i) {
                    if (idx % 3 == 0 && i == 1) continue;
                    if (idx % 3 == 2 && i == 0) continue;
                    int next_idx = idx + dd[i];
                    if (next_idx >= 0 && next_idx < 9) {
                        std::swap(arr[idx], arr[next_idx]);
                        int tmp = arr2num(arr);
                        if (!visited.count(tmp)) {
                            parent[tmp] = now.num;
                            q.push(Node(tmp, now.step+1));
                        }

                        std::swap(arr[idx], arr[next_idx]);
                    }
                }
            }
        }
    }
public:
    void run() {
        runAStar(arr2num(state));
    }
};

#endif

