#include "Node.h"

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

    void addHead(Node *node);

    void remove(Node *node);

};