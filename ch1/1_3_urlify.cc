#include <iostream>
#include <cstring>

using namespace std;

#if 0
void urlify(char *str, int len) {
    int num_sp = 0;

    // scan forward: nums of space
    for (int i = 0; i < len; ++i) 
        if (' ' == str[i]) ++num_sp;

    // move backward and insert %20.
    //   "a b" //-> "a%20b".
    int offset = len + num_sp * 2 - 1;
    for (int i = len-1; i >= 0; --i) {
        //printf("%s, str[%d]:%c\n", str, i, str[i]);
        if (' ' != str[i]) {
            str[offset] = str[i];
            offset--;
        } else {
            str[offset - 2] = '%';
            str[offset - 1] = '2';
            str[offset]     = '0';
            offset -= 3;
        }
    } 
}
#else
void urlify(char *str, int len) {
    // "a b" => "a%20b"
    //  012      01234

    int num_sp = 0;
    for (int i = 0; i < len; ++i) if (str[i] == ' ') num_sp++;

    int offset = len + 2 * num_sp - 1;
    for (int i = len - 1; i >= 0; --i) {
        if (str[i] != ' ') {
            str[offset--] = str[i];
        } else {
            str[offset--] = '0';
            str[offset--] = '2';
            str[offset--] = '%';
        }
    }
}
#endif

int main(void) {
    char input[]  = "Mr John Smith    ";
    char golden[] = "Mr%20John%20Smith";

    int tail_sp = 0;
    int ori_len = strlen(input);
    for(int i = ori_len - 1; i >= 0;--i) {
        if (' ' == input[i]) tail_sp++;
        else break;
    }
    input[ori_len - tail_sp] = '\0';

    printf("original: %s\n", input);
    urlify(input, strlen(input)); //13);
    printf("urlify  : %s\n", input);

    int cmp = strcmp(input, golden);
    printf("%s: %d\n", ((0 == cmp) ? "[PASS]" : "[FAIL]"), cmp);
    return 0;
}
