#include <bits/stdc++.h>

using namespace std;

class Node {
public:
    int key, value, frequency;
    Node *previous, *next;

    Node(int key, int value) {
        this->key = key;
        this->value = value;
        frequency = 1;
    }
};

class frequencyList {
public:
    Node *head, *tail;
    int len;

    frequencyList() {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->previous = head;
        len = 0;
    }

    void addHead(Node *node) {
        Node *currentHead = head->next;
        head->next = node;
        node->previous = head;
        node->next = currentHead;
        currentHead->previous = node;
        len++;
    }

    void remove(Node *node) {
        Node *previousNode = node->previous;
        Node *nextNode = node->next;
        previousNode->next = nextNode;
        nextNode->previous = previousNode;
        len--;
    }
};

class LFUCache {
public:

    unordered_map<int, frequencyList *> frequency;
    unordered_map<int, Node *> mapped_values;
    int capacity, size;
    int minFreq;

    LFUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
        minFreq = 0;
    }

    int get(int key) {
        if (mapped_values.find(key) == mapped_values.end())
            return -1;
        Node *currentNode = mapped_values[key];
        frequency[currentNode->frequency]->remove(currentNode);
        if (minFreq == currentNode->frequency and frequency[currentNode->frequency]->len == 0) {
            minFreq++;
            frequency.erase(currentNode->frequency);
        }
        currentNode->frequency++;
        if (frequency.find(currentNode->frequency) == frequency.end()) {
            frequency[currentNode->frequency] = new frequencyList();
        }
        frequency[currentNode->frequency]->addHead(currentNode);
        mapped_values[key] = currentNode;
        return currentNode->value;
    }

    void put(int key, int value) {
        if (capacity <= 0)return;
        if (mapped_values.find(key) != mapped_values.end()) {
            Node *currentNode = mapped_values[key];
            frequency[currentNode->frequency]->remove(currentNode);
            if (minFreq == currentNode->frequency and frequency[currentNode->frequency]->len == 0) {
                minFreq++;
                frequency.erase(currentNode->frequency);
            }
            currentNode->frequency++;
            currentNode->value = value;
            if (frequency.find(currentNode->frequency) == frequency.end()) {
                frequency[currentNode->frequency] = new frequencyList();
            }
            frequency[currentNode->frequency]->addHead(currentNode);
            mapped_values[key] = currentNode;
            return;
        }
        size++;
        if (size > capacity) {
            Node *evictedNode = frequency[minFreq]->tail->previous;
            mapped_values.erase(evictedNode->key);
            frequency[minFreq]->remove(evictedNode);
            if (frequency[minFreq]->len == 0)
                frequency.erase(minFreq);
            --size;
        }
        Node *currentNode = new Node(key, value);
        if (frequency.find(1) == frequency.end()) {
            frequency[1] = new frequencyList();
            minFreq = 1;
        }
        frequency[1]->addHead(currentNode);
        mapped_values[key] = currentNode;
    }

    void displayCache() {
        if (mapped_values.empty()) {
            cout << "Cache is empty\n" << flush;
            return;
        }
        cout << "BlockNumber\tValue\n" << flush;
        for (auto data : mapped_values) {
            cout << data.first << "\t\t" << data.second->value << "\n" << flush;
        }
    }

    void clearCache() {
        minFreq = 0;
        size = 0;
        mapped_values.clear();
        frequency.clear();
    }
};

int main() {
    int capacity, blockNumber, Value;
    cout << "Enter capacity of your cache :\n" << flush;
    cin >> capacity;
    LFUCache *currentCache = new LFUCache(capacity);
    cout << "Available operations are :\n" << flush;
    cout << "1. f MemoryBlockNumber - Retrieve data from Block if present in cache:\n" << flush;
    cout << "2. i MemoryBlockNumber ValueStored - add block in cache:\n" << flush;
    cout << "3. d - Display current cache:\n" << flush;
    cout << "4. c - Clear Cache\n" << flush;
    cout << "5. e - Exit\n" << flush;
    while (true) {
        string choice;
        cin >> choice;
        if (choice.length() > 1) {
            cout << "Unidentifiable input format!!!\n" << flush;
            continue;
        }
        if (choice[0] == 'e') {
            break;
        }
        if (choice[0] == 'c') {
            currentCache->clearCache();
        } else if (choice[0] == 'd') {
            currentCache->displayCache();
        } else if (choice[0] == 'f') {
            cin >> blockNumber;
            Value = currentCache->get(blockNumber);
            if (Value == -1) {
                cout << "Block not present in Cache\n" << flush;
            } else {
                cout << Value << "\n" << flush;
            }
        } else if (choice[0] == 'i') {
            cin >> blockNumber >> Value;
            currentCache->put(blockNumber, Value);
        } else {
            cout << "Wrong Command!!!\n" << flush;
        }
    }
    return 0;
}