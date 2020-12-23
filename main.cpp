#include<iostream>
#include<unordered_set>
#include<unordered_map>
#include<vector>
#include<queue>
using namespace std;
vector<int> answer { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
int dd[] = { 1, -1, 3, -3 };

int getInvCount(vector<int> arr) {
    int inv_count = 0;
    for (int i = 0; i < 9 - 1; i++)
        for (int j = i + 1; j < 9; j++)
            // Value 0 is used for empty space 
            if (arr[j] && arr[i] && arr[i] > arr[j])
                inv_count++;
    return inv_count;
}

bool isSolvable(vector<int> src, vector<int> tgt) {
    // Count inversions in given 8 puzzle 
    int invSrc = getInvCount(src);
    int invTgt = getInvCount(tgt);

    // return true if inversion count is even. 
    return (invSrc % 2 == invTgt % 2);
}

bool isSolve(vector<int> arr) {
    for (int i = 0; i < 9; ++i) {
        if (arr[i] != answer[i]) return false;
    }
    return true;
}

int arrHash(vector<int> arr) {
    int res = 0;
    for (int i = 0; i < 9; ++i) {
        res = res * 10 + arr[i];
    }
    return res;
}

int zeroIndex(vector<int> arr) {
    for (int i = 0; i < 9; ++i) {
        if (arr[i] == 0) return i;
    }
    return -1;
}

int arr2num(vector<int> arr) {
    int res = 0;
    for (int i = 0; i < 9; ++i) {
        res = res * 10 + arr[i];
    }
    return res;
}

vector<int> num2arr(int num) {
    vector<int> res;
    for (int i = 0; i < 9; ++i) {
        res.push_back(num % 10);
        num /= 10;
    }
    reverse(res.begin(), res.end());

    return res;
}

void outArr(vector<int> arr) {
    for (int i = 0; i < 9; ++i) {
        if (i % 3 == 0) cout << endl;
        cout << arr[i] << ' ';
    }
    cout << endl << "-----" << endl;
}

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
unordered_map<int, int> step;

int AScore(vector<int> arr, int s) {
    int score = s;
    for (int i = 0; i < 9; ++i) {
        score += manhattan[i+1][arr[i]];
    }
    return score;
}




struct cmp {
    bool operator()(int a, int b) {
        int as = AScore(num2arr(a), step[a]);
        int bs = AScore(num2arr(b), step[b]);
        //printf("as: %d, bs: %d \n", as, bs);
        return as > bs;
    }
};

int a = 1;
unordered_map<int, int> Aparent;
unordered_set<int> visited;
int AStar(int arr_) {
    priority_queue<int, vector<int>, cmp> q;
    q.push(arr_);
    while (q.size()) {
        int n = q.size();
        //cout << a++ << endl;
        while (n--) {
            int now = q.top();
            visited.insert(now);
            cout << a++ << endl;
            //cout << now << endl;
            //outArr(num2arr(now));
            if (now == 123456780) return true;
            vector<int> arr = num2arr(now);
            q.pop();
            int idx = zeroIndex(arr);
            for (int i = 0; i < 4; ++i) {
                if (idx % 3 == 0 && i == 1) continue;
                if (idx % 3 == 2 && i == 0) continue;
                int next_idx = idx + dd[i];
                if (next_idx >= 0 && next_idx < 9) {
                    swap(arr[idx], arr[next_idx]);
                    int tmp = arr2num(arr);
                    if (!visited.count(tmp)) {
                        Aparent[tmp] = now;
                        step[tmp] = step[now] + 1;
                        q.push(tmp);
                    }
                    
                    swap(arr[idx], arr[next_idx]);
                }
            }
        }
    }
}



unordered_set<int> st;

int c = 1;
bool dfs(int _arr, int idx, vector<int>& path) {
    vector<int> arr= num2arr(_arr);
    if (!isSolvable(arr, answer) || path.size() >= 50 || st.count(arrHash(arr))) return false;
    st.insert(arrHash(arr));
    if (_arr == 123456780) {
        return true;
    }
    c++;
    //cout << c++ << endl;
    //cout << "!!!!!" << endl;
    for (int i = 0; i < 4; ++i) {
        if (idx % 3 == 0 && i == 1) continue;
        if (idx % 3 == 2 && i == 0) continue;
        int next_idx = idx + dd[i];
        if (next_idx >= 0 && next_idx < 9) {
            swap(arr[idx], arr[next_idx]);
            int tmp = arr2num(arr);
            path.push_back(tmp);
            if (dfs(tmp, next_idx, path)) return true;
            path.pop_back();
            swap(arr[idx], arr[next_idx]);
        }
    }
    return false;
}

unordered_map<int, int> parent;
int b = 1;
bool bfs(int arr_) {
    queue<int> q;
    q.push(arr_);
    while (q.size()) {
        cout << b++ << endl;
        int n = q.size();
        while (n--) {
            int now = q.front();
            if (now == 123456780) return true;
            vector<int> arr = num2arr(now);
            q.pop();
            int idx = zeroIndex(arr);
            for (int i = 0; i < 4; ++i) {
                if (idx % 3 == 0 && i == 1) continue;
                if (idx % 3 == 2 && i == 0) continue;
                int next_idx = idx + dd[i];
                if (next_idx >= 0 && next_idx < 9) {
                    swap(arr[idx], arr[next_idx]);
                    int tmp = arr2num(arr);
                    parent[tmp] = now;
                    q.push(tmp);
                    swap(arr[idx], arr[next_idx]);
                }
            }
        }
    }
    return false;
}

int main() {
    vector<int> start { 1,2,3,4,5,6,0,7,8 };
    vector<int> start2(start);
    vector<int> path;
    //int start_ = arr2num(start);
    //path.push_back(start_);
    //bool solved = dfs(start_, zeroIndex(start), path);
    //for (int arr_: path) {
    //    vector<int> arr = num2arr(arr_);
    //    for (int i = 0; i < 9; ++i) {
    //        if (i % 3 == 0) cout << endl;
    //        cout << arr[i] << ' ';
    //    }
    //    cout << "\n------>\n";
    //}
    //cout << "search count:" << c << endl;
    //cout << "solved: " << solved << endl;
    //cout << "path count: " << path.size() << endl;

    cout << "--------BFS:" << endl;
    bool solved2 = false;
    int start2_ = arr2num(start2);
    solved2 = bfs(start2_);
    int now = 123456780;
    outArr(num2arr(now));
    while (Aparent[now]) {
        outArr(num2arr(Aparent[now]));
        now = Aparent[now];
    }


    //cout << "--------Astar:" << endl;
    //bool solved2 = false;
    //int start2_ = arr2num(start2);
    //solved2 = AStar(start2_);
    //int now = 123456780;
    //outArr(num2arr(now));
    //while (Aparent[now]) {
    //    outArr(num2arr(Aparent[now]));
    //    now = Aparent[now];
    //}


	return 0;
}