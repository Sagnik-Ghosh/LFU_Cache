#include <bits/stdc++.h>
#include "FrequencyList.h"

using namespace std;

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

    int get(int key);

    void put(int key, int value);

    void displayCache();

    void clearCache();

    void incrementFrequency(int key, int value, char c);
};