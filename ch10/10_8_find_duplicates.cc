#include <bits/stdc++.h>

using namespace std;

class BitSet {
protected:
    int *bitset;

public:
    BitSet(int size) {
        bitset = new int[(size >> 5) + 1](); // divide by 32
    }

    ~BitSet(void) {
        delete bitset;
    }

    bool get(int pos) {
        int w = pos >> 5;
        int b = pos & 0x1f;
        return ((bitset[w] & (0x1 << b)) != 0);
    }

    void set(int pos) {
        int w = pos >> 5;
        int b = pos & 0x1f;
        bitset[w] |= (0x1 << b);
    }
};

void check_duplicates(vector<int> data) {
    BitSet bs(32000);

    for (auto num : data) {
        int pos = num - 1; // bitset starts at 0, numbers start at 1
        if (bs.get(pos)) {
            cout << num << " is duplicated." << endl;
        } else {
            bs.set(pos);
        }
    }
}

int main(void) {
    vector<int> data = {1, 2, 3, 3, 4, 5, 6, 7, 7, 7};
    check_duplicates(data);
    return 0;
}
