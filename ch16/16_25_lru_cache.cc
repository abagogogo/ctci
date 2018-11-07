#include <bits/stdc++.h>

using namespace std;

struct Node {
    Node *next;
    Node *prev;
    int key;
    string value;

    Node () {
        next = prev = nullptr;
    }

    Node (int k, string v) {
        next = prev = nullptr;
        key = k;
        value = v;
    }
};

class Cache {
protected:
    int max_cache_size;
    unordered_map<int,Node*> table;
    Node *head;
    Node *tail;

public:
    Cache(int max_size) {
        max_cache_size = max_size;
        head = tail = nullptr;
    }

    // Retrieving value by key.
    string get(int key) {
        auto it = table.find(key);
        if (it != table.end()) {
            Node *node = it->second;
            cout << "DBG: get(" << key << ") = " << node->value << endl;
            update_mru(node);
            return node->value;
        } else {
            cout << "DBG: get(" << key << ") is not found " << endl;
            return "N/A";
        }
    }

    // Inserting key, value pair.
    void set(int key, string value) {
        // remove if already there.
        remove_key(key);

        // if full, remove least recently used item from cache.
        if (table.size() >= max_cache_size) eviction();

        // insert new node.
        Node *node = new Node(key, value);
        insert_head(node);
        table[key] = node;
        cout << "DBG: set(" << key << ", " << value << ")" << endl;
    }
protected:
    // Finding least recently used.
    Node *find_lru(void) {
        return tail;
    }

    // Upating most recently used.
    void update_mru(Node *node) {
        if (node == head) return;
        remove(node);
        insert_head(node);
    }

    // Eviction.
    void eviction(void) {
        Node *node = find_lru();
        if (!node) return;
        cout << "DBG: eviction() on key = " << node->key << endl;
        remove_key(node->key);
    }
    
    // Removing key/value pair from cache, deleting from table and linked list.
    bool remove_key(int key) {
        auto it = table.find(key);
        if (it == table.end()) return false;
        Node *node = it->second;

        table.erase(key);
        remove(node);
        delete node;
        return true;
    }

    void remove(Node *node) {
        Node *prev = node->prev;
        Node *next = node->next;
        if (prev) {
            prev->next = next;
        } else {
            head = next;
        }
        if (next) {
            next->prev = prev;
        } else {
            tail = prev;
        }
    }

    void insert_head(Node *node) {
        if (head) {
            node->prev = nullptr;
            node->next = head;
            head->prev = node;
            head = node;
        } else {
            node->prev = node->next = nullptr;
            head = tail = node;
        }
    }
};

int main(void) {
    Cache cache(3);

    cache.set(0, "a");
    cache.set(1, "b");
    cache.set(2, "c");
    assert(cache.get(2) == "c");
    assert(cache.get(1) == "b");
    assert(cache.get(0) == "a");
    cache.set(3, "d");
    assert(cache.get(2) == "N/A");
    assert(cache.get(1) == "b");
    assert(cache.get(0) == "a");
    assert(cache.get(3) == "d");
    return 0;
}
