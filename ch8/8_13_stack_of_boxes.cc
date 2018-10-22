#include <bits/stdc++.h>

using namespace std;

struct Box {
	int width, depth, height;
	Box(int w, int d, int h) {
		width = w;
        depth = d;
        height = h;
	}

	bool can_be_above(const Box &a) {
		return width < a.width && height < a.height && depth < a.depth;
	}
	static bool compare_h(const Box &b1, const Box &b2) {
		return b1.height >= b2.height;
	}
};


#if 0 // faster, time: 0.921s
//idea:
//	sort boxes in height
//	take one box and the recurse
//	with memoization
// time: O(nlogn + (n-1)*n) = O(n^2)
//
int create_stack(vector<Box> &boxes, int bottom, vector<int> &memo) {
	if (bottom < boxes.size() && memo[bottom] > 0) return memo[bottom];

	Box b = boxes[bottom];
	int max_h = 0;
	for (int i = bottom + 1; i < boxes.size(); ++i) {
		if (boxes[i].can_be_above(b)) {
			int height = create_stack(boxes, i, memo);
			max_h = max(height, max_h);
		}
	}
	max_h += b.height;
	memo[bottom] = max_h;
	return max_h;
}

int create_stack(vector<Box> &boxes) {
	sort(boxes.begin(), boxes.end(), Box::compare_h);
	int max_h = 0;
	// Tallest stack height with box-i at the bottom.
	vector<int> memo(boxes.size(), 0);
	for (int i = 0; i < boxes.size(); ++i) {
		int height = create_stack(boxes, i, memo);
		max_h = max(height, max_h);
	}
	return max_h;
}
#else // time: 4.452s
//
// idea: making a choice at each step, whether to put a particular in the stack.
//
int create_stack(vector<Box> &boxes, Box *bottom, int curr, unordered_map<int, int> &memo) {
    if (curr >= boxes.size()) return 0;

    int height_wi = 0;
    if (bottom == nullptr || boxes[curr].can_be_above(*bottom)) {
        if (memo.find(curr) == memo.end()) {
            memo[curr] = boxes[curr].height + create_stack(boxes, &boxes[curr], curr + 1, memo);
        }
        height_wi = memo[curr];
    }

    int height_wo = create_stack(boxes, bottom, curr + 1, memo);
    return max(height_wi, height_wo);
}

int create_stack(vector<Box> &boxes) {
    sort(boxes.begin(), boxes.end(), Box::compare_h);
    unordered_map<int, int> memo;
    return create_stack(boxes, nullptr, 0, memo);
}
#endif

int main(void) {
    vector<Box> boxes;
#if 0
    boxes.push_back(Box(100, 20, 33));
    boxes.push_back(Box(1, 2, 3));
    boxes.push_back(Box(9, 8, 1));
#else
    srand(123);
    for (int i = 0; i < 10000; ++i) {
        boxes.push_back(Box(rand() % 10000, rand() % 10000, rand() % 10000));
    }
#endif

    cout << create_stack(boxes) << endl;
    return 0;
}
