//
// Created by xyx on 11/11/20.
//

#ifndef TEST_LISTNODE_H
#define TEST_LISTNODE_H
#include <iostream>
struct ListNode
{
    ListNode(int val){this->val = val;}
    ListNode(){;}
    ~ListNode(){;}
    int val;
    ListNode *next = nullptr;
};

void printList(ListNode* head)
{
    while(nullptr != head)
    {
        std::cout<< head->val << "-->";
        head = head->next;
    }
    std::cout<< std::endl;
}
#endif //TEST_LISTNODE_H
