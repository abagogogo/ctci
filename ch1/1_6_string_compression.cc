#include <iostream>
#include <string>

using namespace std;

string do_compress(const string &str) {
    string comp;
    int consec = 1;

    for (int i = 0; i < str.length(); ++i) {
        if (i + 1 < str.length() && str[i] == str[i+1]) {            
            consec++;
        } else {
            comp += str[i];
            comp += to_string(consec);
            consec = 1;
        }
    }
    return (comp.length() < str.length() ? comp : str);
}

int get_compress_len(const string &str) {
    int consec = 1;
    int len = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (i + 1 < str.length() && str[i] == str[i+1]) {
            consec++;
        } else {
            len += to_string(consec).length() + 1;
            consec = 1;
        }
    }
    return len;
}

string better_compress(const string &str) {
    int complen = get_compress_len(str);
    if (complen >= str.length()) return str;

    int consec = 1;
    string comp;
    comp.reserve(complen);

    for (int i = 0; i < str.length(); ++i) {
        if (i + 1 < str.length() && str[i] == str[i+1]) {            
            consec++;
        } else {
            comp.append(str, i, 1);
            comp.append(to_string(consec));
            consec = 1;
        }
    }
    return comp;
}

int main(void) {
    string original = "aabccccaaa";
    string golden   = "a2b1c4a3";
    
    //string compressed = do_compress(original);
    string compressed = better_compress(original);
    cout << ((0 == compressed.compare(golden)) ? "[PASS]" : "[FAIL]");
    cout << original << " => " << compressed << endl;

    return 0;
}
