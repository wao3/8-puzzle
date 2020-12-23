#ifndef E_PUZZLE
#define E_PUZZLE

#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <algorithm>

int arr2num(std::vector<int> arr) {
	int res = 0;
	for (int i = 0; i < 9; ++i) {
		res = res * 10 + arr[i];
	}
	return res;
}

std::vector<int> num2arr(int num) {
	std::vector<int> res;
	for (int i = 0; i < 9; ++i) {
		res.push_back(num % 10);
		num /= 10;
	}
	std::reverse(res.begin(), res.end());
	return res;
}

class puzzle
{
protected:
	int ANSARR[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
	int ANSNUM = 123456780;
	int dd[4] = { 1, -1, 3, -3 };
	std::vector<int> state;
	std::unordered_map<int, int> parent;
	std::unordered_set<int> visited;
	int count = 1;
	bool solved = false;


	bool isSolve(std::vector<int> arr) {
		for (int i = 0; i < 9; ++i) {
			if (arr[i] != ANSARR[i]) return false;
		}
		return true;
	}

	bool isSolve(int num) {
		return isSolve(num2arr(num));
	}

	void outState(std::vector<int> arr) {
		for (int i = 0; i < 9; ++i) {
			if (i % 3 == 0) std::cout << std::endl;
			std::cout << arr[i] << ' ';
		}
		std::cout << std::endl << "-----" << std::endl;
	}

	void outState(int num) {
		outState(num2arr(num));
	}

	int zeroIndex(std::vector<int> arr) {
		for (int i = 0; i < 9; ++i) {
			if (arr[i] == 0) return i;
		}
		return -1;
	}

	int zeroIndex(int num) {
		return zeroIndex(num2arr(num));
	}
public:
	puzzle(std::vector<int> _state) {
		state = _state;
	}
	std::vector<int> getState() {
		return state;
	}

	void setState(std::vector<int> _state) {
		state = state;
	}

	void run() {
	}
};

#endif

