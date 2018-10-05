#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int get_bit(int n, int index)
{
    return ((n & (1 << index)) >> index);
}

void set_bit(int &n, int index, int val)
{
    if (val) {
        n |= (1 << index);
    } else {
        n &= (~(1 << index));
    }
}

int get_next(int n)
{
    int index = 0;
    int count_one = 0;

    if (n <= 0) return -1;

    // find 1st 1
    while (get_bit(n, index) == 0) index++;

    // find 0
    while (get_bit(n, index) == 1) {
        index++;
        count_one++;
    }

    // toggle the 0 to 1
    set_bit(n, index, 1);
    // toggle the 1 at right to 0
    index--;
    set_bit(n, index, 0);
    count_one--;

    // move 1's to right as possible as we can.
    n &= (~((1 << index) - 1));
    n |= ((1 << count_one) - 1);
    return n;
}

int get_prev(int n)
{
    int index = 0;
    int count_one = 0;

    // find 1st zero
    while (get_bit(n, index) == 1) {
        index++;
        count_one++;
    }
    // find 1 pass 0
    while (get_bit(n, index) == 0) {
        index++;
    }
    set_bit(n, index, 0);

    index--;
    set_bit(n, index, 1);

    n &= ~((1 << index) - 1);
    n |= (((1 << count_one) -1) << (index - count_one));

    return n;
}

void updateBits(int *N, int *M, int i, int j)
{
#if 0
    int mask = (~0) << (j + 1);
    mask |= (1 << i) - 1;
    printf("mask = 0x%X\n", mask);

    printf("original N = 0x%X\n", *N);
    *N &= mask;
    printf("after mask N = 0x%X\n", *N);
    *N |= (*M << i);
    printf("M = 0x%X and M << %d = 0x%X\n", *M, i, (*M << i));
    printf("updated N = 0x%X\n", *N);
#else
    if (i > j) return;
    int mask = (1 << (j - i + 1)) - 1;
    printf("mask  = 0x%X\n", mask);
    *N = (*N & (~(mask << i)));
    *N = *N | ((*M & mask) << i );
    printf("updated N = 0x%X\n", *N);
#endif
}

void string2binary(string &input)
{
    size_t pos;
    int int_num = 0;
    double dec_num = 0.0f;
    
    pos = input.find(".");
    if (pos != string::npos) {
        //cout << "int=" << input.substr(0, pos) << endl;
        int_num = atoi(input.substr(0, pos).c_str()); 

        //cout << "double=" << input.substr(pos + 1) << endl;
        dec_num = atof(input.substr(pos).c_str());
    } else {
        int_num = atoi(input.c_str());
    }

    string int_str = "";
    char tmp_str[16];
    cout << "converting integer part: " << int_num << endl;
    while (int_num > 0) {
        sprintf(tmp_str, "%d", (int_num & 0x1));
        int_str = int_str + tmp_str;
        int_num >>= 1;
    }
    cout << int_str << endl;

    string dec_str = "";
    cout << "converting decimal part: " << dec_num << endl;
    int dec_pos = 0;
    while (dec_num > 0.0) {
        if (dec_pos >= 32) {
            cout << "ERROR" << endl;
            break;
        }
        if (dec_num == 1.0f) {
            dec_str = dec_str + "1";
            break;
        }

        dec_num *= 2.0f;
        if (dec_num >= 1.0f) {
            dec_str = dec_str + "1";
            dec_num -= 1.0f;
        } else {
            dec_str = dec_str + "0";
        }
        dec_pos++;
    }
    cout << dec_str << endl;

    cout << input << " = ";
    cout << int_str << "." << dec_str << endl;
}

int find_missing(vector<int> &array, int bit)
{
    if (bit < 0) {
        return 0;
    }

    vector<int> odds;
    vector<int> evens;

    for (typeof(array.begin())it = array.begin(); it != array.end(); it++) {
        if (get_bit(*it, bit) == 0) {
            evens.push_back(*it);
        } else {
            odds.push_back(*it);
        }
    }
    if (odds.size() >= evens.size()) { // remove 0
        return find_missing(evens, bit - 1);
    } else { // remvoe 1
        return ((1 << bit) | find_missing(odds, bit - 1));
    }

}

int find_missing(vector<int> &array)
{
    int n = array.size();    
    int idx;
    for (idx = sizeof(int) * 8 -1; idx >= 0; idx--) {
        if (get_bit(n, idx)) break;
    }
    return find_missing(array, idx);
}

int main(void)
{
    int M = 0x400, N = 0x15;
    string str = "13.75";

    updateBits(&M, &N, 2, 6);
    //updateBits(&M, &N, 2, 3);
    string2binary(str);

    int val = 0x6;
    printf("0x%X next => 0x%X\n", val, get_next(val));
    val = 0x54;
    printf("0x%X next => 0x%X\n", val, get_next(val));

    val = 0x5;
    printf("0x%X prev => 0x%X\n", val, get_prev(val));
    val = 0xa7;
    printf("0x%X prev => 0x%X\n", val, get_prev(val));


    int data[] = {0, 1, 3};
    vector<int> array(data, data + sizeof(data)/sizeof(data[0]));
    int missing = find_missing(array);
    cout << "the missing number is " << missing << endl;

    return 0;
}
