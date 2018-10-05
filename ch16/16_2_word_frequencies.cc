#include <bits/stdc++.h>

using namespace std;

#define SINGLE_QUERY 1
#define HASH_QUERY 2
#define TRIE_QUERY 3

#define METHOD TRIE_QUERY

#if METHOD==SINGLE_QUERY // signle query: O(nw) for each query, for n words in the book and w max word length.
int get_frequency(const vector<string> &book, const string word) {
    int cnt = 0;
    for (auto w : book) {
        if (w == word) ++cnt;
    }
    return cnt;
}
#endif // SINGLE_QUERY

#if METHOD==HASH_QUERY
unordered_map<string, int> *build_dict(const vector<string> &book) {
    unordered_map<string, int> *dict = new unordered_map<string, int>();
    for (auto w : book) (*dict)[w]++;
    return dict;
}

int get_frequency(const vector<string> &book, const string word) {
    static unordered_map<string, int> *dict = build_dict(book);
    return (dict->find(word) != dict->end()) ? (*dict)[word] : 0;
}
#endif // HASH_QUERY

#if METHOD==TRIE_QUERY
#define NUM_CHILD 26

struct TrieNode {
    TrieNode *children[NUM_CHILD];
    int       occur;

    TrieNode(void) {
        memset(children, 0, sizeof(children));
        occur = 0;
    }

    static int index_of(char ch) {
        return tolower(ch) - 'a';
    }

    void insert(const string &word) {
        TrieNode *curr = this;
        for (auto ch : word) {
            int idx = index_of(ch);
            TrieNode *next = curr->children[idx];
            if (!next) {
                next = new TrieNode();
                curr->children[idx] = next;
            }
            curr = next;
        }
        ++curr->occur;
    }

    int search(const string word) {
        TrieNode *node = search_node(word);
        return (node ? node->occur : 0);
    }

    TrieNode *search_node(const string word) {
        const char *str = word.c_str();
        TrieNode *curr = this;
        while (*str) {
            int idx = TrieNode::index_of(*str);
            TrieNode *next = curr->children[idx];
            if (!next) return nullptr;
            curr = next;
            str++;
        }
        return curr;
    }
};

TrieNode *build_trie(const vector<string> &book) {
    TrieNode *root = new TrieNode();
    for (auto w : book) root->insert(w);
    return root;
}

int get_frequency(const vector<string> &book, const string word) {
    static TrieNode *trie = build_trie(book);
    return trie->search(word);
}
#endif // TRIE_QUERY

int main(void) {
    vector<string> words = {
        "note", "that", "a", "problem", "like", "this", "is", "acturally", "relatively", "easy",
        "thus", "the", "interviewer", "is", "going", "to", "be", "looking", "heavily", "at",
        "how", "careful", "you", "are", "did", "you", "check", "for", "error", "condition"
        };
    vector<pair<string, int>> tests = {
        {"you", 2}, {"are", 1}, {"careful", 1}, {"no", 0}, {"ng", 0}
        };

    for (auto q : tests) {
        int ans = get_frequency(words, q.first);
        cout << q.first << " : " << ans << (ans == q.second ? "...[OK]" : "...[NG]") << endl;
    }
    return 0;
}
