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

int dd[] = { 1, -1, 3, -3 };

unordered_set<int> st;

int c = 1;
bool dfs(int _arr, int idx, vector<int>& path) {
    vector<int> arr= num2arr(_arr);
    if (!isSolvable(arr, answer) || st.count(arrHash(arr))) return false;
    st.insert(arrHash(arr));
    if (isSolve(arr)) {
        return true;
    }
    cout << c++ << endl;
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
    vector<int> start { 3,6,5,2,0,7,1,4,8 };
    vector<int> path;
    int start_ = arr2num(start);
    path.push_back(start_);
    bool solved = dfs(start_, zeroIndex(start), path);
    for (int arr_: path) {
        vector<int> arr = num2arr(arr_);
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