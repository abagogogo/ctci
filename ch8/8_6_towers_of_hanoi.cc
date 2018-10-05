#include <bits/stdc++.h>

using namespace std;

class Tower {
protected:
    stack<int> disks_;
    int index_;

public:
    Tower(int index) {
        index_ = index;
    }

    void print(void) {
        cout << "Tower-" << index_ << " size: " << disks_.size() << endl;
    }

    void add(int disk) {
        if (!disks_.empty() && disks_.top() <= disk) {
            cout << "[ERROR] invalid disk size, " << disk << " for tower-" << index_ <<endl;
        } else {
            disks_.push(disk);
        }
    }

    void move_top(Tower &t) {
        int disk = disks_.top(); disks_.pop();
        t.add(disk);
    }

    void move_disks(int n, Tower &destinaion, Tower &buffer) {
        if (n <= 0) return;

        this->move_disks(n - 1, buffer, destinaion);
        this->move_top(destinaion);
        buffer.move_disks(n - 1, destinaion, *this);
    }
};


int main(void) {
    Tower orig(0), dest(1), buffer(2);

    for (int disk = 5; disk > 0; --disk) {
        orig.add(disk);
    }
    orig.move_disks(5, dest, buffer);
    cout << "after moving..." << endl;
    orig.print();
    dest.print();
    buffer.print();

    return 0;
}
