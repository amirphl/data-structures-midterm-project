//
// Created by Yana on 14/12/2017.
//

#ifndef MIDTERMPRO_MYSTACK_H
#define MIDTERMPRO_MYSTACK_H

#include "Service.h"

const int MAX_SIZE = 1000;

class MyStack {
private:
    Node *s = new Node[MAX_SIZE];
    int index = 0;
public:

    Node *top() {
        if (index == 0)
            return nullptr;
        return &s[index - 1];
    }

    int pop() {
        if (index == 0)
            return -1;
        delete (&s[index - 1]);
        index--;
    }

    bool empty() {
        if (!index)
            return 0;
        return 1;
    }

    void push(Node *node) {
        s[index] = *node;
        index++;
    }
};


#endif //MIDTERMPRO_MYSTACK_H
