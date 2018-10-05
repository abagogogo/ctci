#include <bits/stdc++.h>

using namespace std;

void get_count_per_block(vector<int> &data, int range_size, vector<int> &blocks) { 
    for (auto val : data) {
        ++blocks[val / range_size];
    }
}


int find_block_with_missing(vector<int> &blocks, int range_size) {
    for (int i = 0; i < blocks.size(); ++i) {
        //printf("DBG: blocks[%d] = %d\n", i, blocks[i]);
        if (blocks[i] < range_size) return i;
    }
    return -1;
}

unsigned char *get_bit_vector_for_range(vector<int> &data, int &block_idx, int range_size) {
    unsigned char *bit_vector = new unsigned char[range_size / 8]();

    int start = block_idx * range_size;
    int end   = start + range_size;
    //printf("DBG: start=%d, end=%d\n", start, end);
    for (auto val : data) {
        if (val >= start && val < end) {
            int offset = val - start;
            int mask = 1 << (offset % 8);
            //printf("DBG: val=%d => offset=%d, mask=%X\n", val, offset, mask);
            bit_vector[offset / 8] |= mask;
            //printf("DBG: bit_vector[%d] = %X\n", offset / 8, bit_vector[offset/8]);
        }
    }
    return bit_vector;
}

int find_zero(unsigned char *bit_vector, int range_size) {
    int size = range_size / 8;
    for (int i = 0; i < size; ++i) {
        if (bit_vector[i] != 0xff) {
            //printf("DBG: find_zero: bit_vector[%d]=%X\n", i, bit_vector[i]);
            int j;
            for (j = 0; j < 8; ++j) {
                if ((bit_vector[i] & (0x1 << j)) == 0) {
                    //printf("DBG: find_zero: j=%d\n", j);
                    break;
                }
            }
            //printf("DBG: find_zero return offset = %d\n", i * 8 + j);
            return i * 8 + j;
        }
    }
    return -1;
}

int find_open_number(vector<int> data) {
    const int range_size = (1 << 10); // array_size (10 MB = 2^23 byte = 2^21 int ) = 2^31 (non-negative int count) / range_size 
                                      // range_size = 2^10.
    vector<int> blocks((INT_MAX / range_size) + 1, 0);

    // Get count of number of values withing each block.
    get_count_per_block(data, range_size, blocks);    

    // Find a block with a missing value.
    int block_idx = find_block_with_missing(blocks, range_size);
    if (block_idx < 0) return -1;

    // Create bit vector for items within this range.
    unsigned char *bit_vector = get_bit_vector_for_range(data, block_idx, range_size);

    // find a zero in the bit vector.
    int offset = find_zero(bit_vector, range_size);
    delete bit_vector;
    if (offset < 0) return -1;

    // comput the missing value.
    return block_idx * range_size + offset;
}

int main(void) {
    vector<int> data = {6, 5, 1, 7, 8, 9, 2, 3, 10, 0};
    int missing = find_open_number(data);
    cout << missing << " is the missing number" << endl;
    return 0;
}
