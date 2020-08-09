#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

#define tr(c, it) \
        for (typeof(c.begin())it = c.begin(); it != c.end(); it++)

template<class T>
void print_vector(const vector<T> &array, const string name = "")
{
    cout << (name.length() > 0 ? name : "Unknown"); 
    cout << " with " << array.size() << " elements:" << endl;

    tr (array, it) {
        cout << *it << " ";
    }
    cout << endl;
}

vector<int> find_max_sum(const vector<int> &input)
{
    int max_sum = 0;
    int cur_sum = 0;
    bool cont = false;
    vector<int> tmp;
    vector<int> output;

    tr (input, it) {
        cur_sum += *it;
        tmp.push_back(*it);

        if (cur_sum > max_sum) {
            max_sum = cur_sum;

            if (!cont) {
                output.clear();
                tr (tmp, tmp_it) {
                    output.push_back(*tmp_it);
                }
            } else {
                output.push_back(*it);
            }
        } else if (cur_sum < 0) {
            cur_sum = 0;
            tmp.clear();
        }
    }

    cout << "find_max_sum(): max_sum = " << max_sum << endl;
    return output;
}

void rm_punc(string &word)
{
    static char         raw[] = {',', '.', '!', ' '};
    static set<char>    punc(raw, raw + sizeof(raw) / sizeof(raw[0]));

    int idx;
    int len = 0;

    for (idx = word.length() -1; idx >= 0; idx--) {
        if (punc.find(word[idx]) != punc.end()) {
            len++;
        } else {
            break;
        }
    }
    if (len != 0) {
        word.erase(idx + 1, len);
    }
}

void to_lower(string &word)
{
#if 0
    transform(word.begin(), word.end(), word.begin(), ::tolower);
#else
    for (int i = 0; i < word.length(); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            word[i] = word[i] - 'A'+ 'a';
        }
    }
#endif
}

map<string, int> create_dictionary(const string &book_string)
{
    map<string, int>    dic;
    istringstream       book(book_string);
    string              word;
    
    while (book >> word) {
        rm_punc(word);
        to_lower(word);

        if (dic.find(word) != dic.end()) {
            // found
            dic.find(word)->second++;
        } else {
            // 1st time
            dic.insert(pair<string, int>(word, 1));
        }
    }

    return dic;
}

bool key_comp(const pair<string, int>& p1, const pair<string, int>& p2) 
{
    return (p1.first < p2.first);
}

int main(void)
{
    // 19.7 find continuous sequence with the largest sum
    int data[] = {2, -8, 3, -2, 4, -10};
    vector<int> input(data, data + sizeof(data)/sizeof(data[0]));
    vector<int> output;

    print_vector(input);
    output = find_max_sum(input);
    print_vector(output, "output[]");

    // TODO: 19.2 tic-tac-toe

    // TODO: 19.5 Game of Master Mind

    // TODO: 19.8 find the frequency of occurrences of any given word in a book
    string book = "This is a book.\nI like this book...";
    map<string, int> dic = create_dictionary(book);    
    vector< pair<string,int> > sorted_words;
    tr (dic, it) {
        //cout << it->first << " : " << it->second << " times" << endl;
        sorted_words.push_back(pair<string, int>(it->first, it->second));
    }
    sort(sorted_words.begin(), sorted_words.end(), key_comp);
    tr (sorted_words, it) {
        cout << it->first << " : " << it->second << " times" << endl;
    }

    return 0;
}
