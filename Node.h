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