#include <bits/stdc++.h>

using namespace std;

int search(int a[], int left, int right, int x) {
    if (left > right) return -1;

    int mid = (left + right) / 2;
    if (x == a[mid]) return mid;

    // Either the left or right half must be normally orderd.
    // Find out which side is normaly ordered, and then use
    // the normally ordered half to figure out which side 
    // to find x.
    if (a[left] < a[mid]) { // Left is normally ordered.
        if (x >= a[left] && x < a[mid]) {
            return search(a, left, mid, x);
        } else {
            return search(a, mid + 1, right, x);
        }
    } else if (a[left] > a[mid]) { // Right is normally ordered.
        if (x > a[mid] && x <= a[right]) {
            return search(a, mid + 1, right, x);
        } else {
            return search(a, left, mid - 1, x);
        }
    } else if (a[left] == a[mid]) { // Left or right half is all repeats.
        if (a[mid] != a[right]) { // If right is different, search it.
            return search(a, mid + 1, right, x);
        } else { // Else, we have to search both halves.
            int result = search(a, left, mid - 1, x); // search left.
            if (result == -1) {
                return search(a, mid + 1, right, x);
            } else {
                return result;
            }
        }
    }
}

int main(void) {
    int arr[] = {15, 16, 19, 20, 25, 1, 3, 4, 5, 7, 10, 14};
    int cnt = sizeof(arr)/sizeof(arr[0]);
    int x, result;
    
    for (int i = 0; i < cnt; ++i) {
        x = arr[i];
        result = search(arr, 0, cnt - 1, x);
        cout << "search " << x << ": " << result << (result == i ? "...[OK]" : "...[NG]") << endl;;
    }

    return 0;
}
