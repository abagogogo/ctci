#include <bits/stdc++.h>

using namespace std;

//idea:
//	sort boxes in height
//	take one box and the recurse
//	with memoization

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

int main(void) {
    vector<Box> boxes;
    boxes.push_back(Box(100, 20, 33));
    boxes.push_back(Box(1, 2, 3));
    boxes.push_back(Box(9, 8, 1));

    cout << create_stack(boxes) << endl;
    return 0;
}
