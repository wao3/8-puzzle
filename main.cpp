#include<iostream>
#include<unordered_set>
#include<vector>
#include<queue>
using namespace std;
vector<int> answer { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

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

int dd[] = { 1, -1, 3, -3 };

unordered_set<int> st;

bool dfs(vector<int>& arr, int idx, vector<vector<int>>& path) {
    if (!isSolvable(arr, answer) || st.count(arrHash(arr))) return false;
    st.insert(arrHash(arr));
    if (isSolve(arr)) {
        return true;
    }
        
    //cout << "!!!!!" << endl;
    for (int i = 0; i < 4; ++i) {
        if (idx % 3 == 0 && i == 1) continue;
        if (idx % 3 == 2 && i == 0) continue;
        int next_idx = idx + dd[i];
        if (next_idx >= 0 && next_idx < 9) {
            swap(arr[idx], arr[next_idx]);
            path.push_back(arr);
            if (dfs(arr, next_idx, path)) return true;
            path.pop_back();
            swap(arr[idx], arr[next_idx]);
        }
    }
    return false;
}

//int bfs(vector<int>& arr, int idx, vector<vector<int>>& path) {
//    queue<int> q;
//    q.push(idx);
//    while (q.size()) {
//        int n = q.size();
//        while (n--) {
//            int idx_ = q.front();
//
//        }
//    }
//}

int main() {
    vector<int> start { 0,1,2,3,4,5,6,7,8};
    vector<vector<int>> path;
    path.push_back(vector<int>(start));
    bool solved = dfs(start, zeroIndex(start), path);
    for (vector<int> arr: path) {
        for (int i = 0; i < 9; ++i) {
            if (i % 3 == 0) cout << endl;
            cout << arr[i] << ' ';
        }
        cout << "\n------>\n";
    }
    cout << "solved: " << solved << endl;
    cout << "count: " << path.size() << endl;
    //cout << solved;

	return 0;
}